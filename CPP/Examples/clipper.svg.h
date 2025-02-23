/*******************************************************************************
* Author    :  Angus Johnson                                                   *
* Date      :  21 November 2020                                                *
* Website   :  http://www.angusj.com                                           *
* Copyright :  Angus Johnson 2010-2020                                         *
*                                                                              *
* License   : http://www.boost.org/LICENSE_1_0.txt                             *
*******************************************************************************/

#ifndef svglib_h
#define svglib_h

#include <cstdlib>
#include <string>

#include ".\Clipper2Lib\clipper.engine.h"
#include ".\Clipper2Lib\clipper.core.h"

namespace Clipper2Lib {

    class PathInfo {
    private:
        PathsD paths_;
        bool is_open_path;
        unsigned brush_color_;
        unsigned pen_color_;
        double pen_width_;
        bool show_coords_;

    public:
        PathInfo(const PathsD& paths, bool is_open,
            unsigned brush_clr, unsigned pen_clr, double pen_width, bool show_coords) :
            paths_(paths), is_open_path(is_open), brush_color_(brush_clr),
            pen_color_(pen_clr), pen_width_(pen_width), show_coords_(show_coords) {};
        friend class SvgWriter;
        friend class SvgReader;
    };
    typedef std::vector< PathInfo* > PathInfoList;

  //---------------------------------------------------------------------------
  // SvgWriter
  //---------------------------------------------------------------------------

  class SvgWriter
  {
    class CoordsStyle {
    public:
      std::string font_name;
      unsigned font_color = 0xFF000000;
      unsigned font_size = 11;
    };

    class TextInfo {
    public:
        std::string text;
        std::string font_name;
        unsigned font_color = 0xFF000000;
        unsigned font_weight = 600;
        unsigned font_size = 11;
        int x = 0;
        int y = 0;
    public:
        TextInfo(const std::string &txt, const std::string &fnt_name, unsigned color,
            unsigned weight, unsigned size, int coord_x, int coord_y) :
            text(txt), font_name(fnt_name), font_color(color), font_weight(weight), font_size(size),
            x(coord_x), y(coord_y) {};
        friend class SvgWriter;
    };

    typedef std::vector< TextInfo* > TextInfoList;

  private:
      int precision;
      CoordsStyle coords_style;
      TextInfoList text_infos;
      PathInfoList path_infos;
  public:
    SvgWriter(int precision_ = 2): precision(precision_) 
      { fill_rule = FillRule::EvenOdd; coords_style.font_name = "Verdana";
      coords_style.font_color = 0xFF000000; coords_style.font_size = 11; };
    ~SvgWriter() { Clear(); };
    FillRule fill_rule;
    void Clear();
    void SetCoordsStyle(const std::string &font_name, unsigned font_color, unsigned font_size);
    void AddText(const std::string &text, unsigned font_color, unsigned font_size, int x, int y);
    void AddPath(const PathD& path, bool is_open, unsigned brush_color,
      unsigned pen_color, double pen_width, bool show_coords);
    void AddPaths(const PathsD& paths, bool is_open, unsigned brush_color,
      unsigned pen_color, double pen_width, bool show_coords);
    void AddPaths(const Paths64& paths, bool is_open, unsigned brush_color,
      unsigned pen_color, double pen_width, bool show_coords);
    bool SaveToFile(const std::string &filename, int max_width, int max_height, int margin);
  };

  //---------------------------------------------------------------------------
  // SvgReader
  //---------------------------------------------------------------------------

  class SvgReader
  {
  private:
      PathInfoList path_infos;
      bool LoadPath(const std::string& path);
  public:
      std::string xml;
      bool LoadFromFile(const std::string &filename);
      void Clear() { path_infos.clear(); };
      void GetPaths(PathsD& paths);
  };

}

#endif //svglib_h
