# README.md

## Common Errors

1. If you get the error `Segmentation fault (core dumped)` you’re likely trying to stitch together identical images or very large images and thus detecting TON of keypoints and local invariant descriptors (hence the memory error). Instead, load your large images into memory, but then resize them to be be a maximum of 600 pixels along their largest dimension. Perform keypoint detection and matching on the smaller images (we rarely process images larger than 600 pixels along their maximum dimension).

