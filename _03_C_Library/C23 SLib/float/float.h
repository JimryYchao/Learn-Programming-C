#pragma
#define __STDC_VERSION_FLOAT_H__        202311L

#define FLT_ROUNDS                      

#define FLT_IS_IEC_60559	     
#define DBL_IS_IEC_60559	     
#define LDBL_IS_IEC_60559	     

#define FLT_EVAL_METHOD	

#define FLT_HAS_SUBNORM		     
#define DBL_HAS_SUBNORM		     
#define LDBL_HAS_SUBNORM	        

#define FLT_RADIX           

#define INFINITY            
#define NAN     

#define FLT_SNAN            
#define DBL_SNAN            
#define LDBL_SNAN 

#define FLT_MANT_DIG        
#define DBL_MANT_DIG        
#define LDBL_MANT_DIG       

#define FLT_DECIMAL_DIG     
#define DBL_DECIMAL_DIG     
#define LDBL_DECIMAL_DIG    

#define DECIMAL_DIG     

#define FLT_DIG             
#define DBL_DIG             
#define LDBL_DIG            

#define FLT_EPSILON        
#define DBL_EPSILON        
#define LDBL_EPSILON       

#define FLT_MIN            
#define DBL_MIN            
#define LDBL_MIN           

#define FLT_MAX            
#define DBL_MAX            
#define LDBL_MAX  

#define FLT_MIN_EXP         
#define DBL_MIN_EXP         
#define LDBL_MIN_EXP        
 
#define FLT_MAX_EXP         
#define DBL_MAX_EXP         
#define LDBL_MAX_EXP        

#define FLT_MIN_10_EXP      
#define DBL_MIN_10_EXP      
#define LDBL_MIN_10_EXP    

#define FLT_MAX_10_EXP     
#define DBL_MAX_10_EXP     
#define LDBL_MAX_10_EXP   

#define FLT_TRUE_MIN       
#define DBL_TRUE_MIN       
#define LDBL_TRUE_MIN      

#define FLT_NORM_MAX       
#define DBL_NORM_MAX       
#define LDBL_NORM_MAX 


#ifdef __STDC_IEC_60559_DFP__
#define DEC_EVAL_METHOD

#define DEC_INFINITY
#define DEC_NAN

#define DEC32_SNAN
#define DEC64_SNAN
#define DEC128_SNAN

#define DEC32_MANT_DIG
#define DEC64_MANT_DIG
#define DEC128_MANT_DIG

#define DEC32_EPSILON
#define DEC64_EPSILON
#define DEC128_EPSILON

#define DEC32_MIN_EXP
#define DEC64_MIN_EXP
#define DEC128_MIN_EXP

#define DEC32_MAX_EXP
#define DEC64_MAX_EXP
#define DEC128_MAX_EXP

#define DEC32_MIN
#define DEC64_MIN
#define DEC128_MIN

#define DEC32_MAX
#define DEC64_MAX
#define DEC128_MAX

#define DEC32_TRUE_MIN
#define DEC64_TRUE_MIN
#define DEC128_TRUE_MIN
#endif