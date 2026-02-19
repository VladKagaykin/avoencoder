#include<opencv2/opencv.hpp>
#include<iostream>
#include<string>
#include<iomanip>
#include<clocale>
#include<cwchar>
using namespace cv;
using namespace std;
int window_image(string load_image){
    Mat image = imread(load_image);
    if(image.empty()){
        cout <<"Unable to read image: "<< load_image<<endl;
        return -1;
    }
    int width = image.cols;
    int height = image.rows;
    for(int i = 0; i< height; i++){
        for(int j = 0; j< width; j++){
            Vec3b pixel = image.at<Vec3b>(i,j);
            cout << hex
                 << (int)pixel[2] // r
                 << (int)pixel[1] // g
                 << (int)pixel[0] // b
                 << " ";
        }
        cout<<dec<<endl;
    }
    if(height<300 and width<300){
        Mat resized_image;
        resize(image, resized_image, cv::Size(300,300));
        imshow("Resized Image", resized_image);
    }else{
        imshow("Image", image);
    }
    waitKey(0);
    return 0;
}
string text_to_hex(string text){
    string result;
    for(unsigned char c : text){
        char buffer[10];
        sprintf(buffer, "%02x",c);
        result += buffer;
    }
    return result;
}
void encode_text_to_image(string image_path, string text){
    Mat image = imread(image_path);
    if(image.empty()){
        cout <<"Unable to read image: "<< image_path<<endl;
    }
    int width = image.cols;
    int height = image.rows;
    int total_pixels = width *height;
    int max_text_length = total_pixels*3;
    if((int)text.length()>max_text_length){
        cout<<"Text too long"<<endl;
    }
    int idx = 0;
    for(int i = 0; i< height and idx<(int)text.length(); i++){
        for(int j = 0; j< width and idx<(int)text.length(); j++){
            Vec3b& pixel = image.at<Vec3b>(i,j);
            if(idx<(int)text.length()) pixel[2] = text[idx++];
            if(idx<(int)text.length()) pixel[1] = text[idx++];
            if(idx<(int)text.length()) pixel[0] = text[idx++];
        }
    }
    imwrite(image_path, image);
}
string read_image(string load_image){
    Mat image = imread(load_image);
    if(image.empty()){
        cout <<"Unable to read image: "<< load_image<<endl;
    }
    string text = "";
    int width = image.cols;
    int height = image.rows;
    for(int i = 0; i< height; i++){
        for(int j = 0; j< width; j++){
            Vec3b pixel = image.at<Vec3b>(i,j);
            text+=(char)pixel[2];
            text+=(char)pixel[1];
            text+=(char)pixel[0];
        }
    }
    return text;
}
void create_void_image(string encode_text, string img_name, int heigh, int width){
    Mat img(heigh,width, CV_8UC3, Scalar(0,0,0));
    imwrite(img_name, img);
    encode_text_to_image(img_name,encode_text);
}
int main(){
    setlocale(LC_ALL,"");
    string text;
    string temp;
    getline(cin, temp);
    while(temp != ""){
        text += temp;
        text += "\n";
        getline(cin, temp);
    }
    create_void_image(text,"programm.png",48,48);
    return 0;
}