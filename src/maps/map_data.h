#ifndef SRC_MAPS_MAPDATA_H
#define SRC_MAPS_MAPDATA_H



#include <map>
#include <optional>
#include <set>
#include <string_view>

#include "external/commonItems/Color.h"
#include "external/commonItems/ModLoader/ModFilesystem.h"
#include "src/maps/point.h"
#include "src/maps/province_definitions.h"
#include "src/maps/province_points.h"



namespace maps
{

using BorderPoints = std::vector<Point>;
using BordersWith = std::map<std::string, BorderPoints>;


class MapData
{
  public:
   MapData(std::map<std::string, std::set<std::string>> province_neighbors,
       std::map<std::string, BordersWith> borders,
       std::map<std::string, ProvincePoints> the_province_points,
       ProvinceDefinitions province_definitions,
       std::map<Point, std::string> points_to_provinces):
       province_neighbors_(std::move(province_neighbors)),
       borders_(std::move(borders)),
       the_province_points_(std::move(the_province_points)),
       province_definitions_(std::move(province_definitions)),
       points_to_provinces_(std::move(points_to_provinces))
   {
   }

   [[nodiscard]] std::set<std::string> GetNeighbors(const std::string& province) const;
   [[nodiscard]] std::optional<Point> GetSpecifiedBorderCenter(const std::string& main_province,
       const std::string& neighbor) const;
   [[nodiscard]] std::optional<Point> GetAnyBorderCenter(const std::string& province) const;
   [[nodiscard]] std::optional<std::string> GetProvinceName(const Point& point) const;

   [[nodiscard]] std::optional<ProvincePoints> GetProvincePoints(const std::string& province) const;

  private:
   std::map<std::string, std::set<std::string>> province_neighbors_;
   std::map<std::string, BordersWith> borders_;
   std::map<std::string, ProvincePoints> the_province_points_;

   ProvinceDefinitions province_definitions_;
   std::map<Point, std::string> points_to_provinces_;
};

}  // namespace maps



#endif  // SRC_MAPS_MAPDATA_H