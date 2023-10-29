#!/bin/bash
#
# converts all .png or .PNG into a small .jpg file
# with a width of 1080 pixels (height scaled to match). This is done
# so they can be committed to git without bloating the repo
#
# Will throw an error if no .png or .PNG are found, but you can ignore that
#
convert '*.png[1080x]' -strip -interlace Plane -sampling-factor 4:2:0 -quality 70% -define jpeg:dct-method=float -set filename:base "%[basename]" "%[filename:base].jpg";
convert '*.PNG[1080x]' -strip -interlace Plane -sampling-factor 4:2:0 -quality 70% -define jpeg:dct-method=float -set filename:base "%[basename]" "%[filename:base].jpg";

