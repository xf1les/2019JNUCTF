#!/bin/bash

youtube-dl -f 140 'https://www.youtube.com/watch?v=_MMdQL8O3Ds' -o uwasanojinrui.m4a
ffmpeg -i uwasanojinrui.m4a -ss 00:34:50 -to 00:37:16 oneofus.m4a
ffmpeg -i oneofus_orig.m4a -i 51eFtRIwwUL.jpg -i flag.jpg -map 0 -map 1 -map 2 -c copy oneofus.mkv
