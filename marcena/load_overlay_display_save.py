import cv2

img_name = "image.jpg"
compass_name = "compass.png"

img = cv2.imread(img_name)
compass_img = cv2.imread(compass_name, -1)

compass_width = int(img.shape[1]*float(.4))
compass_height = int(img.shape[0]*float(.4))

x_offset=50
y_offset=50

compass_img = cv2.resize (compass_img,(compass_width, compass_height), interpolation = cv2.INTER_CUBIC)

# overlay image1 over imag2 (with transparency support)
# pseudocode:
# [result-image::rgb channel] = [image1::rgb-channel] * [imag1::alpha-channel] + [image2::rgb-channel] * (1.0-[imag1::alpha-channel])
for c in range(0,3):
    img[y_offset:y_offset+compass_img.shape[0], x_offset:x_offset+compass_img.shape[1], c] = compass_img[:,:,c] * (compass_img[:,:,3]/255.0) +  img[y_offset:y_offset+compass_img.shape[0], x_offset:x_offset+compass_img.shape[1], c] * (1.0 - compass_img[:,:,3]/255.0)

# Load the image and show some basic information on it
print "width: %d pixels" % (img.shape[1])
print "height: %d pixels" % (img.shape[0])
print "channels: %d" % (img.shape[2])


# Show the img and wait for a keypress
cv2.imshow("Image", img)
cv2.waitKey(0)

# Save the img -- OpenCV handles converting filetypes
# automatically
cv2.imwrite("newimg.jpg", img)

