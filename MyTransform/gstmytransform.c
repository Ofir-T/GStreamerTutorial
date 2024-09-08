/*
 * GStreamer
 * Copyright (C) 2006 Stefan Kost <ensonic@users.sf.net>
 * Copyright (C) 2024 Ofir <<user@hostname.org>>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

/**
 * SECTION:element-mytransform
 *
 * FIXME:Describe mytransform here.
 *
 * <refsect2>
 * <title>Example launch line</title>
 * |[
 * gst-launch -v -m fakesrc ! mytransform ! fakesink silent=TRUE
 * ]|
 * </refsect2>
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gst/gst.h>
#include <gst/base/base.h>
#include <gst/controller/controller.h>

#include "gstmytransform.h"

GST_DEBUG_CATEGORY_STATIC (gst_mytransform_debug);
#define GST_CAT_DEFAULT gst_mytransform_debug

/* Filter signals and args */
enum
{
  /* FILL ME */
  LAST_SIGNAL
};

enum
{
  PROP_0,
  PROP_SILENT,
};

/* the capabilities of the inputs and outputs.
 *
 * FIXME:describe the real formats here.
 */
static GstStaticPadTemplate sink_template = GST_STATIC_PAD_TEMPLATE ("sink",
    GST_PAD_SINK,
    GST_PAD_ALWAYS,
    GST_STATIC_CAPS ("ANY")
    );

static GstStaticPadTemplate src_template = GST_STATIC_PAD_TEMPLATE ("src",
    GST_PAD_SRC,
    GST_PAD_ALWAYS,
    GST_STATIC_CAPS ("ANY")
    );

#define gst_mytransform_parent_class parent_class
G_DEFINE_TYPE (Gstmytransform, gst_mytransform, GST_TYPE_BASE_TRANSFORM);
GST_ELEMENT_REGISTER_DEFINE (mytransform, "mytransform", GST_RANK_NONE,
    GST_TYPE_MYTRANSFORM);

static void gst_mytransform_set_property (GObject * object,
    guint prop_id, const GValue * value, GParamSpec * pspec);
static void gst_mytransform_get_property (GObject * object,
    guint prop_id, GValue * value, GParamSpec * pspec);

static GstFlowReturn gst_mytransform_transform_ip (GstBaseTransform *
    base, GstBuffer * outbuf);

/* GObject vmethod implementations */

/* initialize the mytransform's class */
static void
gst_mytransform_class_init (GstmytransformClass * klass)
{
  GObjectClass *gobject_class;
  GstElementClass *gstelement_class;

  gobject_class = (GObjectClass *) klass;
  gstelement_class = (GstElementClass *) klass;

  gobject_class->set_property = gst_mytransform_set_property;
  gobject_class->get_property = gst_mytransform_get_property;

  g_object_class_install_property (gobject_class, PROP_SILENT,
      g_param_spec_boolean ("silent", "Silent", "Produce verbose output ?",
          FALSE, G_PARAM_READWRITE | GST_PARAM_CONTROLLABLE));

  gst_element_class_set_details_simple (gstelement_class,
      "mytransform",
      "Generic/Filter",
      "FIXME:Generic Template Filter", "Ofir <<user@hostname.org>>");

  gst_element_class_add_pad_template (gstelement_class,
      gst_static_pad_template_get (&src_template));
  gst_element_class_add_pad_template (gstelement_class,
      gst_static_pad_template_get (&sink_template));

  GST_BASE_TRANSFORM_CLASS (klass)->transform_ip =
      GST_DEBUG_FUNCPTR (gst_mytransform_transform_ip);

  /* debug category for fltering log messages
   *
   * FIXME:exchange the string 'Template mytransform' with your description
   */
  GST_DEBUG_CATEGORY_INIT (gst_mytransform_debug, "mytransform", 0,
      "Template mytransform");
}

/* initialize the new element
 * initialize instance structure
 */
static void
gst_mytransform_init (Gstmytransform * filter)
{
  filter->silent = FALSE;
}

static void
gst_mytransform_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec)
{
  Gstmytransform *filter = GST_MYTRANSFORM (object);

  switch (prop_id) {
    case PROP_SILENT:
      filter->silent = g_value_get_boolean (value);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}

static void
gst_mytransform_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec)
{
  Gstmytransform *filter = GST_MYTRANSFORM (object);

  switch (prop_id) {
    case PROP_SILENT:
      g_value_set_boolean (value, filter->silent);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}

/* GstBaseTransform vmethod implementations */

/* this function does the actual processing
 */
static GstFlowReturn
gst_mytransform_transform_ip (GstBaseTransform * base, GstBuffer * frameBuffer)
{
  //frameBuffer is the current frame buffer. this function works on it in-place.
//  Gstmytransform *filter = GST_MYTRANSFORM (base);
//
//  if (GST_CLOCK_TIME_IS_VALID (GST_BUFFER_TIMESTAMP (outbuf)))
//    gst_object_sync_values (GST_OBJECT (filter), GST_BUFFER_TIMESTAMP (outbuf));
//
//  if (filter->silent == FALSE)
//    g_print ("I'm plugged, therefore I'm in.\n");
//
//  /* FIXME: do something interesting here.  This simply copies the source
//   * to the destination. */
    Gstmytransform *filter = GST_MYTRANSFORM (base);

    // Print timestamp if not in silent mode
    if (GST_CLOCK_TIME_IS_VALID (GST_BUFFER_TIMESTAMP (frameBuffer)) && !filter->silent)
        g_print ("Processing frame at timestamp: %" GST_TIME_FORMAT "\n",
                 GST_TIME_ARGS (GST_BUFFER_TIMESTAMP (frameBuffer)));

    // Access the data in the buffer
    GstMapInfo map;
    if (!gst_buffer_map (frameBuffer, &map, GST_MAP_WRITE)) {
        GST_ERROR ("Failed to map buffer");
        return GST_FLOW_ERROR;
    }

    // Process the frame data here
    // For example, you could perform a simple inversion of pixel values

    guint8 *data = map.data;
    guint size = map.size;

    // Assuming we have raw RGB data and each pixel is 3 bytes (RGB)
    for (guint i = 0; i < size; i += 3) {
        data[i] = 255 - data[i];     // Invert Red
        data[i + 1] = 255 - data[i + 1]; // Invert Green
        data[i + 2] = 255 - data[i + 2]; // Invert Blue
    }

    // Unmap the buffer after processing
    gst_buffer_unmap (frameBuffer, &map);
  return GST_FLOW_OK;
}


/* entry point to initialize the plug-in
 * initialize the plug-in itself
 * register the element factories and other features
 */
static gboolean
mytransform_init (GstPlugin * mytransform)
{
  return GST_ELEMENT_REGISTER (mytransform, mytransform);
}

/* PACKAGE: this is usually set by meson depending on some _INIT macro
 * in meson.build and then written into and defined in config.h, but we can
 * just set it ourselves here in case someone doesn't use meson to
 * compile this code. GST_PLUGIN_DEFINE needs PACKAGE to be defined.
 */
#ifndef PACKAGE
#define PACKAGE "myfirstmytransformtemplate"
#endif

/* gstreamer looks for this structure to register mytransforms
 *
 * FIXME:exchange the string 'Template mytransform' with you mytransform description
 */
GST_PLUGIN_DEFINE (
    GST_VERSION_MAJOR,
    GST_VERSION_MINOR,
    mytransform,
    "mytransform",
    mytransform_init,
    PACKAGE_VERSION, GST_LICENSE, GST_PACKAGE_NAME, GST_PACKAGE_ORIGIN)
