#include "testing/testing.hpp"

#include "kml/serdes_geojson.hpp"
#include "coding/file_reader.hpp"

namespace geojson_tests
{

static kml::FileData LoadGeojsonFromString(std::string_view content)
{
  TEST_NO_THROW(
  {
    kml::FileData dataFromText;
    kml::geojson::GeojsonParser(dataFromText).Parse(MemReader(content));
    return dataFromText;
  }, ());
}


UNIT_TEST(GeoJson_Parse_Basic)
{
  std::string_view constexpr input = R"({
  "type": "FeatureCollection",
  "features": [
    {
      "type": "Feature",
      "properties": {
        "color": "red"
      },
      "geometry": {
        "coordinates": [
          [
            14.949382505528291,
            8.16007148457335
          ],
          [
            26.888888114204264,
            9.708105796659268
          ],
          [
            37.54707497642465,
            6.884595662842159
          ]
        ],
        "type": "LineString"
      }
    },
    {
      "type": "Feature",
      "geometry": {
        "coordinates": [
          31.02177966625902,
          29.8310316130992
        ],
        "type": "Point"
      }
    }
  ]
})";

  kml::FileData const dataFromText = LoadGeojsonFromString(input);

  TEST_EQUAL(dataFromText.m_bookmarksData.size(), 1, ());
  TEST_EQUAL(dataFromText.m_tracksData.size(), 1, ());
}

}  // namespace geojson_tests
