#include <gst/gst.h>
#include <iostream>

#ifdef __APPLE__
#include <TargetConditionals.h>
#endif

int
tutorial_main (int argc, char *argv[])
{
    GstElement *pipeline, *source, *sink, *filter, *converter;
    GstBus *bus;
    GstMessage *msg;
    GstStateChangeReturn ret;

    /* Initialize GStreamer */
    gst_init (&argc, &argv);

    /* Create the elements */
    source = gst_element_factory_make ("v4l2src", "source"); //"videotestsrc" instead of "v4l2src" for synthetic video frames
    sink = gst_element_factory_make ("autovideosink", "sink");
    filter = gst_element_factory_make("mytransform", "filter");
    converter = gst_element_factory_make("videoconvert", "converter");

    /* Create the empty pipeline */
    pipeline = gst_pipeline_new ("test-pipeline");

    if (!pipeline || !source || !sink || !filter || !converter) {
        char buffer[1024];
        sprintf(buffer, "pipeline: %s\nsource: %s\nsink: %s\nfilter: %s\nconverter: %s\n",pipeline ? "true" : "false", source ? "true" : "false", sink ? "true" : "false", filter ? "true" : "false", converter ? "true" : "false");
        g_printerr ("Not all elements could be created.\n");
        std::cout << buffer << std::endl;
        return -1;
    }

    /* Build the pipeline */
    gst_bin_add_many (GST_BIN (pipeline), source, sink, filter, converter, NULL);
    if (gst_element_link_many (source, filter, converter, sink, NULL) != TRUE) {
        g_printerr ("Elements could not be linked.\n");
        gst_object_unref (pipeline);
        return -1;
    }

    /* Modify the source's properties */
    g_object_set (source, "pattern", 0, NULL);

    /* Start playing */
    ret = gst_element_set_state (pipeline, GST_STATE_PLAYING);
    if (ret == GST_STATE_CHANGE_FAILURE) {
        g_printerr ("Unable to set the pipeline to the playing state.\n");
        gst_object_unref (pipeline);
        return -1;
    }

    /* Wait until error or EOS */
    bus = gst_element_get_bus (pipeline);
    msg =
            gst_bus_timed_pop_filtered (bus, GST_CLOCK_TIME_NONE,
                                        (GstMessageType)(GST_MESSAGE_ERROR | GST_MESSAGE_EOS));

    /* Parse message */
    if (msg != NULL) {
        GError *err;
        gchar *debug_info;

        switch (GST_MESSAGE_TYPE (msg)) {
            case GST_MESSAGE_ERROR:
                gst_message_parse_error (msg, &err, &debug_info);
                g_printerr ("Error received from element %s: %s\n",
                            GST_OBJECT_NAME (msg->src), err->message);
                g_printerr ("Debugging information: %s\n",
                            debug_info ? debug_info : "none");
                g_clear_error (&err);
                g_free (debug_info);
                break;
            case GST_MESSAGE_EOS:
                g_print ("End-Of-Stream reached.\n");
                break;
            default:
                /* We should not reach here because we only asked for ERRORs and EOS */
                g_printerr ("Unexpected message received.\n");
                break;
        }
        gst_message_unref (msg);
    }

    /* Free resources */
    gst_object_unref (bus);
    gst_element_set_state (pipeline, GST_STATE_NULL);
    gst_object_unref (pipeline);
    return 0;
}

int
main (int argc, char *argv[])
{
#if defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE
    return gst_macos_main ((GstMainFunc) tutorial_main, argc, argv, NULL);
#else
    return tutorial_main (argc, argv);
#endif
}

