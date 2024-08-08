#include "parse_json.h"
#include <QDebug>

//#pragma execution_character_set("utf-8")

bool LES_Util_Json::parse_json(const QString &str_input, QJsonObject &object)
{
    QByteArray bytes = str_input.toUtf8();  //.toLatin1();
    return parse_json(bytes, object);
}

bool LES_Util_Json::parse_json(const QByteArray &bytes, QJsonObject &object)
{
    QJsonParseError json_error;
    QJsonDocument parse_doc = QJsonDocument::fromJson(bytes, &json_error);

    if (parse_doc.isNull())
    {
        qWarning() << "The data is not json document.";
        return false;
    }

    if (parse_doc.isNull() || json_error.error != QJsonParseError::NoError)
    {
        qWarning() << "parse json info error:" << json_error.errorString();
        return false;
    }

    if (!parse_doc.isObject())
    {
        qWarning() << "The data is not json object.";
        return false;
    }

    object = parse_doc.object();

    return true;
}

bool LES_Util_Json::get_json_value_by_key(const QJsonObject &object, const QString &key,
                                          QString &value)
{
    if (object.contains(key))
    {
        QJsonValue json_value = object.value(key);
        if (json_value.isString())
        {
            value = json_value.toString();
            // qDebug() << key << " :" << value;
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool LES_Util_Json::get_json_value_by_key(const QJsonObject &object, const QString &key, bool &value)
{
    if (object.contains(key))
    {
        QJsonValue json_value = object.value(key);
        if (json_value.isBool())
        {
            value = json_value.toBool();
            // qDebug() << key << " :" << value;
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool LES_Util_Json::get_json_value_by_key(const QJsonObject &object, const QString &key, int &value)
{
    if (object.contains(key))
    {
        QJsonValue json_value = object.value(key);
        if (json_value.isDouble())
        {
            value = json_value.toInt();
            // qDebug() << key << " :" << value;
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool LES_Util_Json::get_json_value_by_key(const QJsonObject &object, const QString &key, double &value)
{
    if (object.contains(key))
    {
        QJsonValue json_value = object.value(key);
        if (json_value.isDouble())
        {
            // qDebug() << " double byzhouxiao" ;
            value = json_value.toDouble();

            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool LES_Util_Json::get_json_value_by_key(const QJsonObject &object, const QString &key,
                                          QJsonObject &value)
{
    if (object.contains(key))
    {
        QJsonValue json_value = object.value(key);
        if (json_value.isObject())
        {
            value = json_value.toObject();
            // qDebug() << key << " : is a object";
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool LES_Util_Json::get_json_value_by_key(const QJsonObject &object, const QString &key,
                                          QVector<unsigned short> &value)
{
    if (object.contains(key))
    {
        QJsonValue json_value = object.value(key);
        if (json_value.isArray())
        {
            QJsonArray array = json_value.toArray();
            int size         = array.size();
            for (int i = 0; i < size; i++)
            {
                if (!array.at(i).isDouble())
                {
                    qWarning() << "some value type is not integer.";
                    return false;
                }
                value.push_back(array.at(i).toInt());
                // qDebug() << key << "[" << i << "] :" << array.at(i).toInt();
            }
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool LES_Util_Json::get_json_value_by_key(const QJsonObject &object, const QString &key,
                                          QSet<unsigned short> &value)
{
    if (object.contains(key))
    {
        QJsonValue json_value = object.value(key);
        if (json_value.isArray())
        {
            QJsonArray array = json_value.toArray();
            int size         = array.size();
            for (int i = 0; i < size; i++)
            {
                if (!array.at(i).isDouble())
                {
                    qWarning() << "some value type is not integer.";
                    return false;
                }
                value.insert(array.at(i).toInt());
                // qDebug() << key << "[" << i << "] :" << array.at(i).toInt();
            }
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool LES_Util_Json::get_json_value_by_key(const QJsonObject &object, const QString &key,
                                          QSet<QString> &value)
{
    if (object.contains(key))
    {
        QJsonValue json_value = object.value(key);
        if (json_value.isArray())
        {
            QJsonArray array = json_value.toArray();
            int size         = array.size();
            for (int i = 0; i < size; i++)
            {
                if (!array.at(i).isString())
                {
                    qWarning() << "some value type is not string.";
                    return false;
                }
                value.insert(array.at(i).toString());
                // qDebug() << key << "[" << i << "] :" << array.at(i).toInt();
            }
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool LES_Util_Json::get_json_value_by_key(const QJsonObject &object, const QString &key,
                                          QVector<QString> &value)
{
    if (object.contains(key))
    {
        QJsonValue json_value = object.value(key);
        if (json_value.isArray())
        {
            QJsonArray array = json_value.toArray();
            int size         = array.size();
            for (int i = 0; i < size; i++)
            {
                if (!array.at(i).isString())
                {
                    qWarning() << "some value type is not string.";
                    return false;
                }
                value.push_back(array.at(i).toString());
            }
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool LES_Util_Json::get_json_value_by_key(const QJsonObject &object, const QString &key,
                                          QJsonArray &value)
{
    if (object.contains(key))
    {
        QJsonValue json_value = object.value(key);
        if (json_value.isArray())
        {
            value = json_value.toArray();
            // qDebug() << key << " : is an array";
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool LES_Util_Json::get_json_optional_value_by_key(const QJsonObject &object, const QString &key,
                                                   bool &value)
{
    if (object.contains(key))
    {
        QJsonValue json_value = object.value(key);
        if (json_value.isBool())
        {
            value = json_value.toBool();
            // qDebug() << key << " :" << value;
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return true;
    }
}

#if 0
bool LES_Util_Json::get_json_id(const QString &str_input, QJsonObject &object, int &id,
                                   bool &internal_code)
{
    if (parse_json(str_input, object) && get_json_value_by_key(object, "id", id)
        && get_json_optional_value_by_key(object, RECODE_JSON_INTERNAL_CODE, internal_code))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool LES_Util_Json::get_json_id(const QString &str_input, int &id, bool &internal_code)
{
    QJsonObject object;
    return get_json_id(str_input, object, id, internal_code);
}
#endif

QString LES_Util_Json::json_object_to_string(const QJsonObject &object)
{
    QJsonDocument document;
    document.setObject(object);
    QByteArray byte_array = document.toJson(QJsonDocument::Compact);

    QString str_json(byte_array);
    return str_json;
}

bool LES_Util_Json::string_to_json(const QString &str_input, QJsonObject &object)
{
    return parse_json(str_input, object);
}
