#include <ft2build.h>
#include FT_FREETYPE_H 

FT_Library    library;
FT_Face       face;
FT_GlyphSlot  slot;
FT_ULong      text[] = { 0x4e2d, 0x6587, 'a', 'b' }; // 中国ab
int           base_x = 0, base_y = 0;

// 初始化一个 lib，多线程的话，每个线程应拥有自己的一个 lib
FT_Init_FreeType( &library );

// 打开 wqy-zenhei.ttf 文件
FT_New_Face( library, "wqy-zenhei.ttf", 0, &face );

// 参数：face, char_width, char_height, horz_resolution, vert_resolution
//
// 设置字号，这里 char_height, vert_resolution 设置 0，表示
// 沿用 char_width, horz_resolution 的值。这里设置 12pt 字号，96dpi
// 注意 12 * 64，因为 FreeType2 中所有 float 都是通过变换成整数来做的，这
// 里是 26.6 float format，所以 (12 << 6) == 12.0
FT_Set_Char_Size(face, 12*64, 0, 96, 0);

// 加载一个具体的字符的 glyph，注意第三个参数，不同的参数可以得到不同的效果
// 加载之后，face->glyph 就是加载好的字体的信息了(包括bitmap)
FT_Load_Char(face, text[0], FT_LOAD_RENDER);

slot = face->glyph;

// 绘制 slot->bitmap;
for ( y = base_y, q = 0; y < bitmap->rows+base_y; y++, q++ )
{
  for ( x = base_x, p = 0; x < bitmap->width+base_x; x++, p++ )
  {
    if ( bitmap->pixel_format == FT_PIXEL_MODE_GRAY )
    {
      // bitmap->buffer 是 256-gray map, one byte / pixel
      offset = y*screen_pitch + x;
      index  = q*bitmap->pitch + p;
      screen_buffer[offset] = bitmap->buffer[index];
    }
    else
    {
      // bitmap->buffer 是 2-gray map, one bit / pixel
      offset = y*screen_pitch + x;
      index  = q*bitmap->pitch + p;
      flag   = bitmap->buffer[index] & (1<<(7-(p%8)));
      screen_buffer[offset] = flag ? BLACK : BGCOLOR;
    }
  }
}

// 绘制这个字符后，应该向右走几个像素
base_x += (slot->advance.x / 64);
