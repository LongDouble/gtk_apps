#ifndef __MONITORING_H__
#define __MONITORING_H__

// Bitmap header size
#define HEADER_SIZE 54

#include <gtk/gtk.h>
#include <string.h>
#include <sys/stat.h>
#include <math.h>
#include "structures.h"

// Called every 100 ms to update the image
gboolean update_bmp(gpointer user_data);

#endif
