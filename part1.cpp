#include <fstream>
#include <string>
#include <sstream>
#include<cstdlib>
#include <cmath>


#include<windows.h>
#include <opencv2/opencv.hpp>
using namespace std;

using namespace cv;




struct QuadTreeNode {
    int x, y, width, height;
    int gray_value;
    bool is_leaf;
    QuadTreeNode* children[4];
};

void build_quadtree(int** arr, int x, int y, int width, int height, QuadTreeNode* node) {
    node->x = x;
    node->y = y;
    node->width = width;
    node->height = height;
    node->gray_value = 0;
    node->is_leaf = false;
    for (int i = 0; i < 4; i++) {
        node->children[i] = nullptr;
    }
    if (width <= 8 || height <= 8) {
        // Leaf node
        int sum = 0;
        for (int i = x; i < x + width; i++) {
            for (int j = y; j < y + height; j++) {
                sum += arr[i][j];
            }
        }
        node->gray_value = sum / (width * height);
        node->is_leaf = true;
    }
    else {
        // Non-leaf node
        int half_width = width / 2;
        int half_height = height / 2;
        node->children[0] = new QuadTreeNode;
        node->children[1] = new QuadTreeNode;
        node->children[2] = new QuadTreeNode;
        node->children[3] = new QuadTreeNode;
        build_quadtree(arr, x, y, half_width, half_height, node->children[0]);
        build_quadtree(arr, x + half_width, y, width - half_width, half_height, node->children[1]);
        build_quadtree(arr, x, y + half_height, half_width, height - half_height, node->children[2]);
        build_quadtree(arr, x + half_width, y + half_height, width - half_width, height - half_height, node->children[3]);
    }
}

//void display_quadtree(QuadTreeNode* node, int depth) {
//    for (int i = 0; i < depth; i++) {
//        cout << "  ";
//    }
//    if (node->is_leaf) {
//        cout << "Leaf node" << endl;
//    }
//    else {
//        cout << "Internal node" << endl;
//        for (int i = 0; i < 4; i++) {
//            if (node->children[i] != nullptr) {
//                display_quadtree(node->children[i], depth + 1);
//            }
//        }
//    }
//}
void save_quadtree(QuadTreeNode* node, ofstream& output_file) {
    if (node == nullptr) {
        return;
    }
    output_file << node->x << " " << node->y << " " << node->width << " " << node->height << " " << node->gray_value << " " << node->is_leaf << endl;
    for (int i = 0; i < 4; i++) {
        save_quadtree(node->children[i], output_file);
    }
}






int main()
{
  
    cv::Mat img, cpy, ground;
    img = cv::imread("C:\\Users\\fahad\\OneDrive\\Desktop\\t1.bmp", cv::IMREAD_GRAYSCALE);
    img.convertTo(cpy, CV_32S, 1, 0);
    int** arr = new int* [cpy.rows];
    for (int i = 0; i < cpy.rows; ++i) {
        arr[i] = cpy.ptr<int>(i);
    }
    int nmbr_of_rows = img.rows;
    int nmbr_of_cols = img.cols;
    QuadTreeNode* root = new QuadTreeNode;
    build_quadtree(arr, 0, 0, nmbr_of_cols, nmbr_of_rows, root);
    //    
   // display_quadtree(root, 0);
   ofstream output_file;
    output_file.open("quadtree1.txt");
     save_quadtree(root, output_file);
    output_file.close();


    ofstream output_file1;
        output_file1.open("row_col.txt");     //write the number of rows and col in file to use in part2
   
    output_file1 << nmbr_of_rows << " " << nmbr_of_cols << endl;
    output_file1.close();
    cout << "Succesfully written quad tree in file"<<endl;
    return 0;

}