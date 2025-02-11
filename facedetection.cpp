#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream> // For file check
#include <direct.h>  // To get the current working directory

int main() {
    // Print the current working directory
    char buf[256];
    _getcwd(buf, sizeof(buf));  // Get current working directory
    std::cout << "Current Working Directory: " << buf << std::endl;

    // Path to the Haar cascade for face detection
    std::string faceCascadePath = "C:\\Users\\KUNAL AGRAWAL\\source\\repos\\Face Recognition system\\haarcascade_frontalface_default.xml";


    // Check if the Haar cascade file exists
    std::ifstream file(faceCascadePath);
    if (!file) {
        std::cerr << "Error: Could not find the Haar cascade file at specified path." << std::endl;
        return -1;
    }

    // Load the Haar cascade for face detection
    cv::CascadeClassifier faceCascade;
    if (!faceCascade.load(faceCascadePath)) {
        std::cerr << "Error: Could not load Haar cascade file." << std::endl;
        return -1;
    }

    // Open the default camera (ID 0)
    cv::VideoCapture camera(0);
    if (!camera.isOpened()) {
        std::cerr << "Error: Could not open the camera." << std::endl;
        return -1;
    }

    // Create a window to display the video feed
    cv::namedWindow("Face Recognition", cv::WINDOW_AUTOSIZE);

    cv::Mat frame, grayFrame;

    std::cout << "Press ESC to exit the program." << std::endl;

    while (true) {
        // Capture a new frame
        camera >> frame;

        if (frame.empty()) {
            std::cerr << "Error: Captured an empty frame." << std::endl;
            break;
        }

        // Convert the frame to grayscale (required for Haar cascades)
        cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);

        // Detect faces
        std::vector<cv::Rect> faces;
        faceCascade.detectMultiScale(grayFrame, faces, 1.1, 10, 0, cv::Size(30, 30));

        // Draw rectangles around detected faces
        for (const auto& face : faces) {
            cv::rectangle(frame, face, cv::Scalar(255, 0, 0), 2);
        }

        // Display the frame with detected faces
        cv::imshow("Face Recognition", frame);

        // Break the loop if the ESC key is pressed
        if (cv::waitKey(1) == 27) {
            std::cout << "ESC key pressed. Exiting..." << std::endl;
            break;
        }
    }

    // Release the camera and close all OpenCV windows
    camera.release();
    cv::destroyAllWindows();

    return 0;
}
