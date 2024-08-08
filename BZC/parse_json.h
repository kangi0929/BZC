#pragma once
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

// zhouxiao  JSON
#define JSON_KEY_ID      "id"
#define JSON_PANORAMA_IP "panorama_ip"
#define JSON_DEVICE      "device"
#define JSON_MAC         "mac"
#define JSON_THRESHOLD   "threshold"

#define JSON_AREA_DATA  "area_data"
#define JSON_AREA_ID    "area_id"
#define JSON_POINT_DATA "point_data"
#define JSON_ORDER_NO   "order_no"
#define JSON_X_POS      "x_pos"
#define JSON_Y_POS      "y_pos"

class LES_Util_Json
{
public:
    /*
    解析JSON数据，获取JSON对象
    str_input:input
    object:output

    return: bool 成功返回true,失败返回false
                                           */
    static bool parse_json(const QString &str_input, QJsonObject &object);

    static bool parse_json(const QByteArray &bytes, QJsonObject &object);

    /*
    根据JSON对象和KEY,获取对应的值信息
    object:input
    key:input
    value:output

    return: bool 成功返回true,失败返回false
                                           */
    static bool get_json_value_by_key(const QJsonObject &object, const QString &key, QString &value);
    static bool get_json_value_by_key(const QJsonObject &object, const QString &key, bool &value);
    static bool get_json_value_by_key(const QJsonObject &object, const QString &key, int &value);
    static bool get_json_value_by_key(const QJsonObject &object, const QString &key,
                                      QJsonObject &value);
    static bool get_json_value_by_key(const QJsonObject &object, const QString &key,
                                      QVector<unsigned short> &value);
    static bool get_json_value_by_key(const QJsonObject &object, const QString &key,
                                      QSet<unsigned short> &value);
    static bool get_json_value_by_key(const QJsonObject &object, const QString &key,
                                      QSet<QString> &value);
    static bool get_json_value_by_key(const QJsonObject &object, const QString &key,
                                      QVector<QString> &value);
    static bool get_json_value_by_key(const QJsonObject &object, const QString &key,
                                      QJsonArray &value);

    static bool get_json_value_by_key(const QJsonObject &object, const QString &key, double &value);

    /*
     * 获取可选参数信息
     * 若参数不存在，参数存在且类型正确返回true；
     * 参数存在，但参数类型不正确返回false。
     */
    static bool get_json_optional_value_by_key(const QJsonObject &object, const QString &key,
                                               bool &value);

    /*
    解析JSON数据，获取JSON对象和操作ID
    str_input:input
    object:output
    value:output
    internal_code: output 是否为内部操作码

    return: bool 成功返回true,失败返回false

             static bool get_json_id(const QString &str_input, QJsonObject &object, int &id,
                         bool &internal_code);
    static bool get_json_id(const QString &str_input, int &id, bool &internal_code);
    */

    /*
把QJsonObject对象转换为QString
*/
    static QString json_object_to_string(const QJsonObject &object);

    static bool string_to_json(const QString &str_input, QJsonObject &object);
};
