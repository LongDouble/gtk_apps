# bmp\_monitor

Monitors a bitmap for changes and displays the most up-to-date version of the image.  If the amount of expected data (bitmap is assumed to have no compressed and 24-bit pixel format) for the bitmap's width and height is not present, the occupied area of the bitmap is drawn on a canvas from the top down.  When the next bitmap is detected, it is loaded automatically.

Usage: ./bmp\_monitor <file-prefix>

Example: If the bitmaps generated are located in /home/admin and will be generated with names frame1.bmp, frame2.bmp, frame3.bmp, and so on, then the proper way to run the program is:

./bmp\_monitor /home/admin/frame
