#include<hitOrMiss/hit_or_miss.hpp>
#include<fstream>
#include<ctikz/ctikz.hpp>


int main(int argc, char** argv)
{
    int test_case = 1;
    int max_test_num = 10;
    std::cout<<("Enter the test number from 1 to " + std::to_string(max_test_num) + ":\n");
    std::cin >> test_case;
    std::cout << "\n";

    if (test_case<1 || test_case>max_test_num) {
        printf("The number entered is not from the specified range!");
        return -1;
    }

    std::string test_path = "..//tests/test_" + std::to_string(test_case) + "/";

    std::ifstream check_image(test_path + "image.png");
    std::ifstream check_kernel_foreground(test_path + "kernel_foreground.png");
    std::ifstream check_kernel_background(test_path + "kernel_background.png");
    std::ifstream check_hit_highlight(test_path + "hit_highlight.png");
    std::ifstream check_test_type_hit(test_path + "hit_or_miss.png");
    std::ifstream check_test_type_boundary(test_path + "boundary_extraction.png");
    std::ifstream welcome_message(test_path + "README.txt");

    std::string line;
    while (std::getline(welcome_message, line))
    {
        std::cout << line<<"\n";
    }

    cv::Mat image{};
    cv::Mat kernel_foreground{};
    cv::Mat kernel_background{};
    cv::Mat hit_highlight{};
    cv::Mat test_type_hit{};
    cv::Mat test_type_boundary{};

    if (check_image.good()) image = cv::imread(test_path + "image.png", cv::IMREAD_GRAYSCALE);
    if (check_kernel_foreground.good()) kernel_foreground = cv::imread(test_path + "kernel_foreground.png", cv::IMREAD_GRAYSCALE);
    if (check_kernel_background.good()) kernel_background = cv::imread(test_path + "kernel_background.png", cv::IMREAD_GRAYSCALE);
    if (check_hit_highlight.good()) hit_highlight = cv::imread(test_path + "hit_highlight.png", cv::IMREAD_GRAYSCALE);
    if (check_test_type_hit.good()) test_type_hit = cv::imread(test_path + "hit_or_miss.png", cv::IMREAD_GRAYSCALE);
    if (check_test_type_boundary.good()) test_type_boundary = cv::imread(test_path + "boundary_extraction.png", cv::IMREAD_GRAYSCALE);


    HitOrMiss test;

    
    if (image.empty() && kernel_foreground.empty() && kernel_background.empty() && hit_highlight.empty()) {
        test = HitOrMiss();
    }
    else if (!image.empty() && kernel_foreground.empty() && kernel_background.empty() && hit_highlight.empty()) {
        test = HitOrMiss (image);
    }
    else if (!image.empty() && !kernel_foreground.empty() && kernel_background.empty() && hit_highlight.empty()) {
        test = HitOrMiss (image, kernel_foreground);
    }
    else if (!image.empty() && !kernel_foreground.empty() && !kernel_background.empty() && hit_highlight.empty()) {
        test = HitOrMiss (image, kernel_foreground, kernel_background);
    }
    else if (!image.empty() && !kernel_foreground.empty() && !kernel_background.empty() && !hit_highlight.empty()) {
        test = HitOrMiss (image, kernel_foreground, kernel_background, hit_highlight);
    }
    else {
        printf("Wrong input format\n");
    }

    cv::Mat result_hit_or_miss = test.DoHitOrMiss();
    cv::Mat result_boundary_extraction = test.DoBoundaryExtraction();    
    

    if (test_type_hit.empty() && test_type_boundary.empty()) {
        printf("Operation type not selected\n");
        return -1;
    }
    
    cv::imshow("Input Image", test.get_image());
    cv::moveWindow("Input Image", 0, 0);

    if (!test_type_hit.empty()) {
        cv::imshow("Result of Hit or Miss", result_hit_or_miss);
        cv::moveWindow("Result of Hit or Miss", 0, test.get_image().rows + 50);
    }
    
    if (!test_type_boundary.empty()) {
        cv::imshow("Result of Boundary Extraction", result_boundary_extraction);
        cv::moveWindow("Result of Boundary Extraction", 0, test.get_image().rows + 50);
    }

    CTikz latex;
    latex.start_picture();
    FigureStyle style;
    style.thickness = "very thin";
    style.color = "black";
    style.fill = "white";

    //вывод изначальной картинки в латех
    for (int temp_row = 0; temp_row < test.get_image().rows; temp_row += 1) {
        for (int temp_col = 0; temp_col < test.get_image().cols; temp_col += 1) {
            
            if (test.get_image().at<uchar>(temp_row, temp_col) == 0) {
                style.fill = "black";
            }
            else {
                style.fill = "white";
            }

            latex.drawRectangle(temp_col, test.get_image().rows-temp_row, temp_col+1,
                test.get_image().rows - temp_row + 1, style);
        }
    }

    //повторный вывод картинки справа
    for (int temp_row = 0; temp_row < test.get_image().rows; temp_row += 1) {
        for (int temp_col = 0; temp_col < test.get_image().cols; temp_col += 1) {

            if (test.get_image().at<uchar>(temp_row, temp_col) == 0) {
                style.fill = "black";
            }
            else {
                style.fill = "white";
            }

            latex.drawRectangle(temp_col + test.get_image().cols+5, test.get_image().rows - temp_row,
                temp_col + 1 + test.get_image().cols + 5, test.get_image().rows - temp_row + 1, style);
        }
    }

    //наложение маски на 2 экран
    FigureStyle kernel_style;
    kernel_style.custom = "color=red, dashed, ultra thick, fill opacity=0.7,";
    latex.drawRectangle(test.get_image().cols + 5, test.get_image().rows - test.get_kernel_foreground().rows+1,
        test.get_kernel_foreground().cols + test.get_image().cols + 5, test.get_image().rows, kernel_style);

    FigureStyle mask;
    mask.custom = "color=red, dashed, ultra thick, fill=white, fill opacity=0.7";

    for (int temp_row = 0; temp_row < test.get_kernel_foreground().rows; temp_row += 1) {
        for (int temp_col = 0; temp_col < test.get_kernel_foreground().cols; temp_col += 1) {

            if (test.get_kernel_foreground().at<uchar>(temp_row, temp_col) == 0) {
                mask.custom = "color=black, dashed, ultra thick, fill = green!20";
            }
            else {
                mask.custom = "color=white, dashed, ultra thick, fill=white";
            }

            latex.drawRectangle(temp_col + test.get_image().cols + 5, test.get_image().rows - temp_row,
                temp_col + 1 + test.get_image().cols + 5, test.get_image().rows - temp_row + 1, mask);
        }
    }

    //результат 3 экран
    cv::Mat result = !test_type_hit.empty() ? result_hit_or_miss : result_boundary_extraction;
    for (int temp_row = 0; temp_row < test.get_image().rows; temp_row += 1) {
        for (int temp_col = 0; temp_col < test.get_image().cols; temp_col += 1) {

            if (result.at<uchar>(temp_row, temp_col) == 0) {
                style.fill = "black";
            }
            else {
                style.fill = "white";
            }

            latex.drawRectangle(temp_col, test.get_image().rows - temp_row - test.get_image().rows-5, temp_col + 1,
                test.get_image().rows - temp_row + 1 - test.get_image().rows - 5, style);
        }
    }
    
    latex.end_picture();
    latex.create_tikz_file("visualization");
 
    cv::waitKey();
}