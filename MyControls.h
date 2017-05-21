#ifndef MYCONTROLS_H
#define MYCONTROLS_H
#include <map>
#include <string>

/*  maybe the UI control need inherit this class
 */
class MyCtrlObj
{
public:
    MyCtrlObj(std::string key = "");
    ~MyCtrlObj();
    std::string& GetObjName();
    // maybe not useful in gcc
    std::string& GetTypeName();
private:
    std::string m_obj_name;
    std::string m_type_name;
    static int l_count;
};

/*  author: kpli
 *  date:   2017.5.21
 *  feature:
 *      connect between UI control and Model
 *  note:
 *      it's useful when our program need UI control,
 *      the model only access this class rather than access UI control directly.
 */
class MyCtrls
{
public:
    static MyCtrls* GetInst();
    void* Get(const std::string);
    int RegCtrl(const std::string,void *);
    int UnRegCtrl(const std::string);
private:
    MyCtrls();
    bool Find(std::string);
    static MyCtrls* instance;

    std::map<std::string,void*> m_ctrl;
};

#endif // MYCONTROLS_H
