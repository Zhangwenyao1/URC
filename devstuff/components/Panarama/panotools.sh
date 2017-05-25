# Dependencies: sudo apt install hugin-tools enblend
set -x # echo on

# create project file
pto_gen -o pano.pto $1
# do cpfind
cpfind -o pano.pto --multirow --celeste pano.pto
# do clean
cpclean -o pano.pto pano.pto
# do vertical lines
linefind -o pano.pto pano.pto
# do optimize locations
autooptimiser -a -m -l -s -o pano.pto pano.pto
# calculate size
pano_modify --canvas=AUTO --crop=AUTO -o pano.pto pano.pto
# stitch
hugin_executor --stitching --prefix=output pano.pto
# compress
convert output.tif output.png
