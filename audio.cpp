#include <stdlib.h>
#include <string>
#include <gst/gst.h>
#include <glib.h>



//gst-launch-1.0 audiotestsrc freq=600 ! audioconvert ! autoaudiosink

void alert(float freq)
{
    GstElement *pipeline, *source, *convert, *sink;
    GMainLoop* loop = nullptr;     
    GstBus *bus = nullptr;


    pipeline = gst_pipeline_new ("audio");
    source = gst_element_factory_make ("audiotestsrc","source");
    convert = gst_element_factory_make ("audioconvert", "con");
    sink = gst_element_factory_make ("autoaudiosink", "sink");
    
    if (!pipeline || !source || !convert || !sink ) 
    {
        g_printerr ("One element could not be created. Exiting.\n");
    }

    g_object_set(G_OBJECT(source), "freq", freq , NULL);
    
    gst_bin_add_many(GST_BIN(pipeline), source, convert, sink, NULL);

    if (!gst_element_link_many (source, convert, sink, NULL)) 
    {
        fprintf(stderr,"Elements could not be linked.\n");
        gst_object_unref (pipeline);
    }
      /* Set the pipeline to "playing" state*/
    //g_print ("Now playing...\n");
    gst_element_set_state (pipeline, GST_STATE_PLAYING);

    /* Iterate */
    //g_print ("Running...\n");
    loop = g_main_loop_new (NULL, FALSE);
    //g_main_loop_run (loop);
    int exit_loop = 0;
    while (++exit_loop<1000000)
    {
        g_main_context_iteration(g_main_loop_get_context(loop), FALSE);
    }
    //g_main_loop_quit(loop);


    /* Out of the main loop, clean up nicely */
    g_print ("Returned, stopping playback\n");
    gst_element_set_state (pipeline, GST_STATE_NULL);

    g_print ("Deleting pipeline\n");
    gst_object_unref (GST_OBJECT (pipeline));
    //g_main_loop_unref (loop);

}

int main (int argc, char** argv)
{
    gst_init(NULL, NULL);
    int freq = 600;
    alert(freq);

    return 0; 
}
