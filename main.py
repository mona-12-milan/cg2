
import cv2
import matplotlib.pyplot as plt
import numpy as np
from skimage.exposure import match_histograms
from PIL import Image

































# cvtColor(img,cv2.COLOR_BGR2HSV)
img1 = cv2.imread("img1.jpg")
img2 = cv2.imread("img2.jpg")
img3 = cv2.imread("img3.png")
img4 = cv2.imread("img4.jpg")


'''
#-------------------------HISTOGRAM------------------------------
cv2.imshow("image",img2)

plt.hist(img1.ravel(),256,[0,256])
plt.hist(img2.ravel(),256,[0,256])
plt.show()

'''


'''

#----------------------------THRESHOLDING--------------------------

#to convert it to grayscale

img = cv2.cvtColor(img3, cv2.COLOR_BGR2GRAY)
ret, thresh1 = cv2.threshold(img,120,255,cv2.THRESH_BINARY)
ret, thresh2 = cv2.threshold(img,120,255,cv2.THRESH_BINARY_INV)
ret, thresh3 = cv2.threshold(img,120,255,cv2.THRESH_TRUNC)
ret, thresh4 = cv2.threshold(img,120,255,cv2.THRESH_TOZERO)
ret, thresh5 = cv2.threshold(img,120,255,cv2.THRESH_TOZERO_INV)


cv2.imshow("original grayscale",img)
cv2.imshow("THRESH_BINARY",thresh1)
cv2.imshow("THRESH_BINARY_INV",thresh2)
cv2.imshow("THRESH_TRUNC",thresh3)
cv2.imshow("THRESH_TOZERO",thresh4)
cv2.imshow("THRESH_TOZERO_INV",thresh5)


'''

'''  

#-------------------------------------HISTOGRAM EQUALIZATION----------------------------
cv2.imshow("image",img1)
img = cv2.cvtColor(img1, cv2.COLOR_BGR2GRAY)
equ = cv2.equalizeHist(img)
res = np.hstack((img,equ))

cv2.imshow("histogram Equalization", res)


'''


'''

#------------------------------------------hISTOGRAM MATCHING-------------------------------------------

matched = match_histograms(img1, img2)

fig, (ax1, ax2, ax3) = plt.subplots(nrows=1, ncols=3,
                                    figsize=(8, 3),
                                    sharex=True, sharey=True)

for aa in (ax1, ax2, ax3):
    aa.set_axis_off()

ax1.imshow(img1)
ax1.set_title('Source')
ax2.imshow(img2)
ax2.set_title('Reference')
ax3.imshow(matched)
ax3.set_title('Matched')

plt.tight_layout()
plt.show()

'''

'''

#-------------------------------Intensity Transfer---------------------------------------

image = Image.open('img1.jpg')
data = np.asarray(image)
data = abs(255-data)

intensity_image = Image.fromarray(data)
intensity_image.save("new_img1.jpg")

new_img1 = cv2.imread("new_img1.jpg")

data = abs(200-data)
intensity_image = Image.fromarray(data)
intensity_image.save("new_img2.jpg")

new_img2 = cv2.imread("new_img2.jpg")
cv2.imshow("old img",img1)
cv2.imshow("new img",new_img1)
cv2.imshow("new img2",new_img2)


'''

'''

#-----------------------------------Morphological operations-------------------------------
kernel = np.ones((5, 5), np.uint8)


invert = cv2.threshold(img4,205,255,cv2.THRESH_BINARY_INV)[1]
erosion = cv2.erode(invert,kernel,iterations = 3)
dilation = cv2.dilate(invert,kernel,iterations = 3)
opening = cv2.morphologyEx(invert,cv2.MORPH_OPEN,kernel,iterations = 5)
closing = cv2.morphologyEx(invert,cv2.MORPH_CLOSE,kernel,iterations = 5)
gradient = cv2.morphologyEx(invert,cv2.MORPH_GRADIENT , kernel , iterations = 1)

grayimg = cv2.cvtColor(invert, cv2.COLOR_BGR2GRAY)
print(grayimg)
hit_miss = cv2.morphologyEx(grayimg, cv2.MORPH_HITMISS, kernel,iterations = 4)

#cv2.imshow("inverted image", invert)

#cv2.imshow("eroded image" , erosion)
#cv2.imshow("dialated image" , dilation)
#cv2.imshow("opening image" , opening)
#cv2.imshow("closing image" , closing)
#cv2.imshow("gradient image" , gradient)


cv2.imshow("grayimg" , grayimg)
cv2.imshow("hit or miss" , hit_miss)


'''

'''
#--------------------------------------------EDGE DETECTION----------------------
#canny laplacian sobel

image_gray = cv2.cvtColor(img2,cv2.COLOR_BGR2GRAY)
canny1 = cv2.Canny(image_gray,threshold1 = 20 , threshold2 = 200)
# for laplacian we need to use gaussian filter to remove noise

img = cv2.GaussianBlur(image_gray,(3,3) , 0)
laplacian = cv2.convertScaleAbs(cv2.Laplacian(img,ksize=3, ddepth=cv2.CV_16S))

sobel_x_filtered_image = cv2.Sobel(image_gray, cv2.CV_64F, 1, 0, ksize=3)
sobel_x_filtered_image = cv2.Sobel(image_gray, cv2.CV_64F, 0, 1, ksize=3)
sobel_y_filtered_image = cv2.convertScaleAbs(sobel_x_filtered_image)
sobel_y_filtered_image = cv2.convertScaleAbs(sobel_y_filtered_image)
cv2.imshow("normal" , img2)
cv2.imshow("canny1" ,canny1)
cv2.imshow("laplacian" , laplacian)
cv2.imshow("sobel_x" , sobel_x_filtered_image)
cv2.imshow("soble y" , sobel_y_filtered_image)

'''

'''

#----------------------------------------SPACIAL FILTERS-----------------------------------

meanImage = cv2.blur(img2,(3,3))

meadianImage = cv2.medianBlur(img2,3)
gaussianImage1 = cv2.GaussianBlur(img2,(3,3) , 4)
gaussianImage2 = cv2.GaussianBlur(img2,(3,3) , 10)

cv2.imshow("normal" , img2)
cv2.imshow("mean img" , meanImage)
cv2.imshow("median img" , meadianImage)
cv2.imshow("Gaussian img1" , gaussianImage1)
cv2.imshow("Gaussian img2" , gaussianImage2)

'''


'''
#---------------------------------------------SHARPENING----------------------------------------

sharp_kernel = np.array([[0, -1, 0],
                         [-1, 5, -1],
                         [0, -1, 0]])

sharp_img = cv2.filter2D(src=img3, ddepth=-1, kernel=sharp_kernel)

# Showing the sharpened image using matplotlib library function plt.imshow()
plt.imshow(sharp_img)
plt.show()


'''

'''

#--------------------------------------------EMBOSS------------------------------------------------

emboss_kernel = np.array([[-1, 0, 0],
                          [0, 0, 0],
                          [0, 0, 1]])

# Embossed image is obtained using the variable emboss_img
# cv2.fliter2D() is the function used
# src is the source of image(here, img)
# ddepth is destination depth. -1 will mean output image will have same depth as input image
# kernel is used for specifying the kernel operation (here, emboss_kernel)
emboss_img = cv2.filter2D(src=img3, ddepth=-1, kernel=emboss_kernel)
plt.imshow(emboss_img)
plt.show()


'''


'''
#------------------------------------------CONTRAST-STRECH---------------------------------


import cv2
import numpy as np

# Function to map each intensity level to output intensity level.
def pixelVal(pix, r1, s1, r2, s2):
	if (0 <= pix and pix <= r1):
		return (s1 / r1)*pix
	elif (r1 < pix and pix <= r2):
		return ((s2 - s1)/(r2 - r1)) * (pix - r1) + s1
	else:
		return ((255 - s2)/(255 - r2)) * (pix - r2) + s2

# Define parameters.
r1 = 70
s1 = 0
r2 = 140
s2 = 255

# Vectorize the function to apply it to each value in the Numpy array.
pixelVal_vec = np.vectorize(pixelVal)

# Apply contrast stretching.
contrast_stretched = pixelVal_vec(img1, r1, s1, r2, s2)

# Save edited image.
cv2.imwrite('contrast_stretch.jpg', contrast_stretched)

img5 = cv2.imread("contrast_stretch.jpg")
cv2.imshow("contrast strech" , img5)


'''

'''
#-------------------------------------------LOW PASS------------------------------

kernel = np.array([[1, 1, 1, 1, 1], [1, 1, 1, 1, 1], [1, 1, 1, 1, 1], [1, 1, 1, 1, 1], [1, 1, 1, 1, 1]])
img = cv2.filter2D(img2, -1, kernel / sum(kernel))
cv2.imshow('Low pass Image', img)


#-------------------------------------------HIGH PASS--------------------------------

kernel = np.array([[0, -1, 0], [-1, 4, -1], [0, -1, 0]])
img = cv2.filter2D(img2, -1, kernel)
cv2.imshow('High Pass Image', img)

kernel = np.array([[0, -1, 0], [-1, 5, -1], [0, -1, 0]])
img_color = cv2.filter2D(img2, -1, kernel)
cv2.imshow('Color High Pass Image', img_color)

'''



cv2.waitKey(0)
cv2.destroyAllWindows()