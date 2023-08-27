# Import necessary libraries
import cvzone
import cv2
from cvzone.HandTrackingModule import HandDetector
from cvzone.SerialModule import SerialObject

# Initialize the webcam capture
cap = cv2.VideoCapture(0)

# Create a HandDetector object that detects 1 hand at a time and a detection confidence threshold set to 0.7 (minimum value a detected object should have to be a valid detection)
detector = HandDetector(maxHands=1, detectionCon=0.7)

# Create a SerialObject to establish serial communication with Arduino
mySerial = SerialObject("COM5", 9600, 1)

# Start an infinite loop to continuously process frames from the webcam
while True:
    success, img = cap.read()   # Read a frame from the webcam
    
    hands, bboxInfo = detector.findHands(img)    # Use the HandDetector to find hands in the frame and get bounding box info for each hand

    # If at least one hand is detected
    if hands:        
        fingers = detector.fingersUp(hands[0])# Get the finger state (up or down) for the detected hand
                
        print(fingers)  # Print the finger state (a list of 5 binary values indicating if each finger is up or down) - for testing purposes
        
        mySerial.sendData(fingers)  # Send the finger state data over serial communication to Arduino
       
    cv2.imshow("Image", img) # Display the image with any drawn overlays (hand landmarks, bounding boxes)
        
    if cv2.waitKey(1) & 0xFF == 27: # Check for key press events and exit the loop if the Esc key is pressed
        break

# Release the webcam capture and close all OpenCV windows
cap.release()
cv2.destroyAllWindows()
