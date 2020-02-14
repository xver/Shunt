#define MY_HOST "localhost"
#define MY_PORT  3450
/*
  Function: shunt_cs_comp_intV
  compare two intV payloads

  Parameters:
  h - cs_header
  lhs,rhs - intA data
  Returns:
  success > 0
*/
int shunt_cs_comp_intV   (cs_header* h,int *lhs,int *rhs) {
  int success = 1;
  //compare
  if (h->data_type==  shunt_prim_hash("SHUNT_INT")) {
    for (int i=0;i< h->n_payloads;i++) {
      if(lhs[i] != rhs[i]) success = 0;
    }
  }
  return success;
}
/*
  Function: shunt_cs_print_intV
  print out IntV Data

  Parameters:

  h - cs_data_header structure
  Int  - Data to print
  msg  - print out prefix

  Returns:
  void
*/
void shunt_cs_print_intV   (cs_header* h,int *Int,char* msg) {
  if (h->data_type==  shunt_prim_hash("SHUNT_INT")) {
    for (int i=0;i< h->n_payloads;i++) {
      printf("\n %s IntV[%0d]=%d",msg,i,Int[i]);
    }
  }
  puts("\n");
}
/*
  Function: shunt_cs_comp_doubleV
  compare two doubleV payloads

  Parameters:
  h - cs_header
  lhs,rhs - double V data
  Returns:
  success > 0
*/
int shunt_cs_comp_doubleV   (cs_header* h,double *lhs,double *rhs) {
  int success = 1;
  if (h->data_type==  shunt_prim_hash("SHUNT_REAL")) {
    for (int i=0;i< h->n_payloads;i++) {
      if(lhs[i] != rhs[i]) success = 0;
    }
  }
  return success;
}
/*
  Function: shunt_cs_print_doubleV
  print out DoubleV Data

  Parameters:

  h - cs_data_header structure
  Double  - Data received
  msg    - print out prefix

  Returns:
  void
*/
void shunt_cs_print_doubleV   (cs_header* h,double *Double,char* msg) {
  
  if (h->data_type==  shunt_prim_hash("SHUNT_REAL")) {
    for (int i=0;i< h->n_payloads;i++) {
      printf("\n %s DoubleV[%0d]=%f",msg,i,Double[i]);
    }
  }
}

/*
  Function: shunt_cs_comp_byteV
  compare two char * payloads

  Parameters:
  h - cs_header
  lhs,rhs - string
  Returns:
  success > 0
*/
int shunt_cs_comp_byteV   (cs_header* h,char *lhs,char *rhs) {
  int success = 1;
  if (h->data_type ==  shunt_prim_hash("SHUNT_BYTEV")) {
    for (int i=0;i< h->n_payloads;i++) {
      if(lhs[i] != rhs[i]) success = 0;
    }
  }
  return success;
}
/*
  Function: shunt_cs_print_ByteA
  print out ByteA Data

  Parameters:
  n_payloads - number of data payloads
  h - cs_data_header structure
  Byte  - Data to print
  msg    - print out prefix
  Returns:
   void
*/
void shunt_cs_print_byteA   (int n_payloads,cs_data_header* h,char *ArrayS,char* msg) {
  int indx_ =0;
  for(int i=0;i<n_payloads;i++) {
    for (int j=0;j< h->trnx_payload_sizes[i];j++) {
      printf("\n %s (%0d) ArrayS[%0d][%0d]=%d",msg,indx_,i,j,ArrayS[indx_]);
      indx_++;
    }
  }
  puts("\n");
}

/*
  Function: shunt_cs_print_LongV
  print out DoubleV Data

  Parameters:

  h - cs_data_header structure
  Long  - Data received
  msg    - print out prefix

  Returns:
  void
*/
void shunt_cs_print_longV   (cs_header* h,long int *Long,char* msg) {
  
  if (h->data_type==  shunt_prim_hash("SHUNT_LONGINT")) {
    for (int i=0;i< h->n_payloads;i++) {
      printf("\n %s LongV[%0d]=%ld",msg,i,Long[i]);
    }
  }
}

/*
  Function: shunt_cs_comp_longV
  compare two longV payloads

  Parameters:
  h - cs_header
  lhs,rhs - long V data
  Returns:
  success > 0
*/
int shunt_cs_comp_longV   (cs_header* h,long int *lhs,long int *rhs) {
  int success = 1;
  if (h->data_type==  shunt_prim_hash("SHUNT_LONGINT")) {
    for (int i=0;i< h->n_payloads;i++) {
      if(lhs[i] != rhs[i]) success = 0;
    }
  }
  return success;
}
