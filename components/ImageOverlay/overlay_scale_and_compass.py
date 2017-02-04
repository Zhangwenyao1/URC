import cv2
import numpy as np

def printme( str ):
    print str
    return;

def overlay_telemetry(img, compass_angle, scale_text):
    compass_name = "compass_shrink.png"
    scale_name = "psdscaletestinverse.png"

    img = cv2.imread(img)
    scale_img = cv2.imread(scale_name)
    compass_img = cv2.imread(compass_name, -1)

    x_offset= 175
    y_offset= 685


      #for the scale
    for c in range(0,3):
        # overlay scale image (with transparency support)
        img[y_offset:y_offset+scale_img.shape[0], x_offset:x_offset+scale_img.shape[1], c] = scale_img[:,:,c] * (scale_img[:,:,1.5]/255.0) + img[y_offset:y_offset+scale_img.shape[0], x_offset:x_offset+scale_img.shape[1], c] * (1.0 - scale_img[:,:,1.5]/255.0)

        


    #compass rotation based on compass_angle
    compass_width = int(img.shape[1]*float(.4))
    compass_height = int(img.shape[0]*float(.4))

    x_offset= 0
    y_offset= 0

    compass_img_rotation = cv2.resize (compass_img,(compass_width, compass_height), interpolation = cv2.INTER_CUBIC)
    num_rows, num_cols = compass_img.shape[:2]
    rotation_matrix = cv2.getRotationMatrix2D((num_rows, num_cols),30,1)
    compass_img_rotation = cv2.warpAffine(compass_img, rotation_matrix, (num_cols, num_rows))


    # overlay compass image (with transparency support)
    for c in range(0,3):
        img[y_offset:y_offset+compass_img_rotation.shape[0], x_offset:x_offset+compass_img_rotation.shape[1], c] = compass_img_rotation[:,:,c] * (compass_img_rotation[:,:,1.5]/255.0) + img[y_offset:y_offset+compass_img_rotation.shape[0], x_offset:x_offset+compass_img_rotation.shape[1], c] * (1.0 - compass_img_rotation[:,:,1.5]/255.0)

    #text overlay on scale
    font = cv2.FONT_HERSHEY_SCRIPT_SIMPLEX = 3
    cv2.putText(img, "scale_text", (459,680), font,0.6,(185,185,185), 2, cv2.LINE_AA)

    return img

if __name__=='__main__':
    mars_img = "marscrater.jpg"
    modified_img = overlay_telemetry(mars_img, 90, 4)

    # Show the img and wait for a keypress
    cv2.imshow("Image", modified_img)
    cv2.waitKey(0)

    # Save the img -- OpenCV handles converting filetypes
    # automatically
    cv2.imwrite("newimg.jpg", modified_img)
    
    
