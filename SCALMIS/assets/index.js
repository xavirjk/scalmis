function returnRespectiveField(ref){
    if(ref.pjno)return ref.pjno
    return ref.fullname
}
function truncated(modelData){
    const statement = modelData.assetId?
                        modelData.assetId.description+ " "+modelData.itemId.item:modelData.itemId.item
    return baseTr(31, statement);
}

function truncateOffice (modelData){
    const statement = modelData.refMember?
                        modelData.refMember.office: modelData.member.office
    return baseTr(18, statement);
}

function truncateName(modelData){
    const statement = modelData.refMember?
                        returnRespectiveField(modelData.refMember): modelData.member.fullName
    if(typeof statement === Number) return statement;
    return baseTr(18,statement);
}

function baseTr(i,text){
    const len = text.length;
    if(len < i) return text;
    return text.substring(0, i)+"..";
}

function indexOfEq(model, val){
    for(let i = 0; i < model.length; i++){
        if(model[i].ui_value === val) return model[i].ui_key;
    }
    return 0;
}
