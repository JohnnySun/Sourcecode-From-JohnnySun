#include <ft2build.h>
#include FT_FREETYPE_H

int main(int argc, char **argv){
  int psize;
  FT_Library library;
  FT_Face face;
  unsigned int ucode;
  FT_UInt glyph_index;
  int row, pixel;

  if(argc != 4){
    return 10;
  }

  ucode = strtol(argv[2], NULL, 10);
  psize = strtol(argv[3], NULL, 10);

  printf("unicode +%X size %d\n", ucode, psize);
  if(FT_Init_FreeType(&library)
     || FT_New_Face(library,
                    argv[1],
                    0,
                    &face)
     || FT_Set_Pixel_Sizes(face,
                           psize,
                           0)){
    return 1;
  }

  glyph_index = FT_Get_Char_Index(face, ucode);
  if(glyph_index == 0){
    return 2;
  }
  if(FT_Load_Glyph(face,
                   glyph_index,
                   FT_LOAD_DEFAULT)){
    return 3;
  }
  if(FT_Render_Glyph(face->glyph,
                     FT_RENDER_MODE_MONO)){
    return 4;
  }
  printf("bitmap_left=%d\n"
         "bitmap_top=%d\n"
         "bitmap.rows=%d\n"
         "bitmap.width=%d\n"
         "bitmap.pitch=%d\n"
         "bitmap.pixel_mode=%d\n",
         face->glyph->bitmap_left,
         face->glyph->bitmap_top,
         face->glyph->bitmap.rows,
         face->glyph->bitmap.width,
         face->glyph->bitmap.pitch,
         face->glyph->bitmap.pixel_mode);
  printf("\n\n");
  for(row = 0;
      row < (face->glyph->bitmap.rows - face->glyph->bitmap_top);
      ++row){
      for(pixel = 0; pixel < face->glyph->bitmap.width; ++pixel){
        printf("_");
      }
      printf("\n");
  }
  for(row = 0; row < face->glyph->bitmap.rows; ++row){
    for(pixel = 0; pixel < face->glyph->bitmap_left; ++pixel)
      printf("_");
    for(pixel = 0; pixel < face->glyph->bitmap.width; ++pixel){
      printf("%c", (face->glyph->bitmap.buffer
                    [row * face->glyph->bitmap.pitch +
                     pixel/8] & (0xC0 >> (pixel % 8)))?'O':'_');
    }
    printf("\n");
  }
  return 0;
}
