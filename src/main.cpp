#include <iostream>
using std::cout, std::cerr, std::endl;

#include <Magick++.h>
using Magick::InitializeMagick, Magick::Image, Magick::Geometry, Magick::Color;


int main(int /*argc*/, char ** argv){
  InitializeMagick(*argv);

  Image sample_img;
  sample_img.read("img_input/cat.jpg");
  sample_img.display();


  unsigned int base_width = sample_img.columns();
  unsigned int base_height = sample_img.rows();
  unsigned int squared_side;
  if (base_width != base_height) {
    squared_side = std::min(sample_img.columns(), sample_img.rows());
    unsigned int delta_side = std::abs(int(base_width - base_height));
    bool is_wide = base_width > base_height;
    sample_img.chop(Geometry(is_wide?delta_side/2:0, is_wide?0:delta_side/2));
    sample_img.crop(Geometry(squared_side, squared_side));
  } else {
    squared_side = base_width;
  }
  unsigned int new_side = squared_side/2;
  sample_img.resize(Geometry(new_side, new_side));
  unsigned int n_horizontal = 2;
  unsigned int n_vertical = 2;
  unsigned int pad_width = 30;
  unsigned int pad_height = 30;


  Image support_image(Geometry(new_side*n_horizontal+pad_width, new_side*n_vertical+pad_height), Color(MaxRGB, 0, 0, 0));
  support_image.composite(sample_img, pad_width/3, pad_height/3);
  sample_img.rotate(90);
  support_image.composite(sample_img, pad_width/3, 2*pad_height/3+new_side);
  sample_img.rotate(90);
  support_image.composite(sample_img, 2*pad_width/3+new_side, pad_height/3);
  sample_img.rotate(90);
  support_image.composite(sample_img, 2*pad_width/3+new_side, 2*pad_height/3+new_side);
  support_image.display();
  
  support_image.magick("png");
  support_image.write("img_out/composed_img.png");



  return 0;
}
