#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include<cstdlib>
#include <cmath>
#include<stack>

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

void load_quadtree(QuadTreeNode* node, ifstream& input_file) {
    if (node == nullptr) {
        return;
    }
    input_file >> node->x >> node->y >> node->width >> node->height >> node->gray_value >> node->is_leaf;
    if (!node->is_leaf) {
        node->children[0] = new QuadTreeNode;
        node->children[1] = new QuadTreeNode;
        node->children[2] = new QuadTreeNode;
        node->children[3] = new QuadTreeNode;
        for (int i = 0; i < 4; i++) {
            load_quadtree(node->children[i], input_file);
        }
    }
}
int main()
{
    int nmbr_of_rows, nmbr_of_cols;
    ifstream output_file1("E:\\test\\test\\row_col.txt");     //extracting number of rows and cols
    
    output_file1 >> nmbr_of_rows >> nmbr_of_cols;
    output_file1.close();
  
    QuadTreeNode* node = new QuadTreeNode;
    ifstream input_file;
    input_file.open("E:\\test\\test\\quadtree1.txt");
    load_quadtree(node, input_file);
    input_file.close();

    int** arr1 = new int* [nmbr_of_rows];//arr for image
    for (int i = 0; i < nmbr_of_rows; i++)
    {
        arr1[i] = new int[nmbr_of_cols];
    }

    // Backtraversal
    stack<QuadTreeNode*> nodes;
    nodes.push(node);
    while (!nodes.empty()) {
        QuadTreeNode* current_node = nodes.top();
        nodes.pop();
        if (current_node->is_leaf) {
           
            for (int i = current_node->x; i < current_node->x + current_node->width; i++) {
                for (int j = current_node->y; j < current_node->y + current_node->height; j++) {
                    arr1[i][j] = current_node->gray_value;
                }
            }
        }
        else {
            // Add all child to the stack
            for (int i = 0; i < 4; i++) {
                if (current_node->children[i] != nullptr) {
                    nodes.push(current_node->children[i]);
                }
            }
        }
    }

    // Reconstruct image from array
    Mat reconstructed_image(nmbr_of_rows, nmbr_of_cols, CV_8UC1);
    for (int i = 0; i < nmbr_of_rows; i++) {
        for (int j = 0; j < nmbr_of_cols; j++) {
            reconstructed_image.at<unsigned char>(i, j) = static_cast<unsigned char>(arr1[i][j]);
        }
    }

   
    namedWindow("Reconstructed Image", WINDOW_NORMAL);
    imshow("Reconstructed Image", reconstructed_image);
    imwrite("reconstructed_image.jpg", reconstructed_image);
    waitKey(0);



    return 0;

}
