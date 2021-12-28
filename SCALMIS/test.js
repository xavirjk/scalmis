const genCode = () => {
  var sym = ['!', '@', '#', '$', '%', '^', '&', '*', '=', '-', '_'];
  var Alphabets = 'abcdefghijklmnopqrstuvwzyz';
  var pwdChars =
    '0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz';
  var pwdLen = 2;
  var randPassword = Array(pwdLen)
    .fill(pwdChars)
    .map(function (x) {
      return x[Math.floor(Math.random() * x.length)];
    })
    .join('');
  let randSym = sym[getRand(sym.length)];
  let randNum = getRand(10);
  let randAlpha = Alphabets[getRand(Alphabets.length)];
  return (
    randPassword + `${randAlpha.toUpperCase()}${randSym}${randNum}${randAlpha}`
  );
};

function getRand(max) {
  return Math.floor(Math.random() * max);
}

console.log(genCode());
//var regE = /^(?=.*[a-z])(?=.*[A-Z])(?=.*[0-9])(?=.*[!@#-_=\$%\^&\*]).{6,24}$/;
//var regE = /^(?=.*[a-z])(?=.*[A-Z])(?=.*[0-9])(?=.*[!@#-_=$%^&*]).{6,24}$/;
var regE = /^[a-zA-Z0-9._-]{6}$/;
console.log(regE.test('zne4y.'));
