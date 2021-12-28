#include "validators.h"
#include <map>
namespace SCALMIS {
namespace validators {

class Validators::Implementation {
public:Implementation(Validators *_validators, const QString _key = ""):
        validators(_validators), key(_key)
    {
    }
    Validators *validators{nullptr};
    QString key;
    QRegularExpression emailRe,stringRe,passwordRe,codeRe, pjRe;
    bool isValid = false;
    std::map<QString,QRegularExpression> Res = {
        {"string",stringRe},
        {"email",emailRe},
        {"password",passwordRe},
        {"code",codeRe},
        {"pjno",pjRe},
    };

private:
    void setValid(){
        isValid = true;
    }
};
Validators::Validators(QObject *parent, const QString key) : QObject(parent)
{
    implementation.reset(new Implementation(this,key));

    implementation->Res.at("code").setPattern("^[A-Z0-9]{10,40}$");
    implementation->Res.at("pjno").setPattern("^[0-9]{10}$");
    implementation->Res.at("string").setPattern("^[a-zA-Z0-9 .'&,-_@]{2,80}$");
    implementation->Res.at("password").setPattern("^(?=.*[a-z])(?=.*[A-Z])(?=.*[0-9])(?=.*[!@#-_=$%^&*]).{6,24}$");
    //implementation->Res.at("password").setPattern("^[a-zA-Z0-9 .'&,-_@#]{6,40}$");
    implementation->Res.at("email").setPattern("^[a-zA-Z0-9._-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,4}$");
}

void Validators::validate(const QString &data){
    if(implementation->Res.find(implementation->key) == std::end(implementation->Res)) {
        implementation->key = "string";
    }
    QRegularExpression re = implementation->Res.find(implementation->key)->second;
    re.setPatternOptions(QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionMatch match =  re.match(data);
    if(match.hasMatch()){
        implementation->isValid = true;
    }
    else implementation->isValid = false;
}

bool Validators::validated(){
    return implementation->isValid;
}

Validators::~Validators(){}
}
}

