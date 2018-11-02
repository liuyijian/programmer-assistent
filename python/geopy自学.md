# geopy

###地理编码和逆地理编码

```python
>>> import json
>>> from geopy.geocoders import Nominatim

# 构造定位器，若无ssl权限，则先在python3.7文件夹中找到一个自带的install certificate的东西安装
>>> geolocator = Nominatim(user_agent="my-application")

# 构造地点
>>> location = geolocator.geocode("175 5th Avenue NYC")

# 地点地址
>>> location.address
Flatiron Building, 175, 5th Avenue, Flatiron, New York, NYC, New York, ...

# 地点经纬度 
>>> (location.latitude, location.longitude)
(40.7410861, -73.9896297241625)

# 地点详细信息
>>> json.dumps(location.raw)
{
    "place_id": "138642704",
    "licence": "Data \u00a9 OpenStreetMap contributors, ODbL 1.0. https://osm.org/copyright",
    "osm_type": "way",
    "osm_id": "264768896",
    "boundingbox": [
        "40.7407597",
        "40.7413004",
        "-73.9898715",
        "-73.9895014"
    ],
    "lat": "40.7410861",
    "lon": "-73.9896298241625",
    "display_name": "Flatiron Building, 175, 5th Avenue, Flatiron District, Manhattan, Manhattan Community Board 5, New York County, NYC, New York, 10010, USA",
    "class": "tourism",
    "type": "attraction",
    "importance": 0.793003315521974,
    "icon": "https://nominatim.openstreetmap.org/images/mapicons/poi_point_of_interest.p.20.png"
}

# 经纬度反定位
>>> location = geolocator.reverse("52.509669, 13.376294")
```

### 计算经纬度距离和球面距离

```python
>>> from geopy.distance import vincenty
>>> from geopy.distance import great_circle

>>> tiananmen = (39.9073285, 116.391242416486)
>>> xiaozhai = (34.2253171, 108.9426205)
# vincenty生成的Distance对象的属性有：meters，kilometers，miles，nautical（海里），ft（英尺）
>>> print(vincenty(tiananmen, xiaozhai).meters)
913925.3164971869

>>> print(great_circle(tiananmen, xiaozhai).meters)
913657.4596518736
```