#pragma once

#define MustNotNull(p) { if (p==NULL) return; }
#define MustNotNullResult(p, result) { if (p==NULL) return result; }

#define MustBeFalse(p) { if(p==true) return; }
#define MustBeFalseResult(p, result) { if(p==true) return result; }

#define MustBeTrue(p) { if(p==false) return; }
#define MustBeTrueResult(p, result) { if(p==false) return result; }