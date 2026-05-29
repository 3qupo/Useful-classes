import cv2
import time
import numpy as np
import os

os.environ["OPENCV_VIDEOIO_PRIORITY_MSMF"] = "0"
os.environ["OPENCV_VIDEOIO_DEBUG"] = "1"

cap = cv2.VideoCapture(0)

if not cap.isOpened(): 
    print("Cannon open camera")
    exit()

filter_mode = 0   # 0 - original
            # 1 - grey
            # 2 - blur

while True:
    ret, frame = cap.read()

    if not ret:
        break

    key = cv2.waitKey(1) & 0xFF
        
    if key == ord('1'):
        filter_mode = 1
    elif key == ord('2'):
        filter_mode = 2

    if filter_mode == 1:
        gray_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        cv2.imshow("Gray_Frame", gray_frame)
    elif filter_mode == 2:
        gaussian_blur = cv2.GaussianBlur(frame, (15, 15), 0)
        cv2.imshow("Blur", gaussian_blur)
        

    cv2.imshow("My_own_video", frame)

    if cv2.waitKey(25) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()