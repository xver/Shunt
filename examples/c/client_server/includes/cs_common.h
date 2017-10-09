#define MY_HOST "localhost"
#define MY_PORT  3450
#define SIZE_STRING 17
#define SIZE_VECTOR 17
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
  Function: shunt_cs_comp_header
  compare two SHUNT headers

  Parameters:
  
  h_lhs,h_rhs - two cs headers
  Returns:
  
  success > 0
*/
int shunt_cs_comp_header  (cs_header h_lhs,cs_header h_rhs) {
  int success = 1;
  if (h_lhs.data_type != h_rhs.data_type) success = 0;
  if (h_lhs.trnx_id   != h_rhs.trnx_id) success = 0;
  if (h_lhs.trnx_type != h_rhs.trnx_type) success = 0;
  if (h_lhs.n_payloads!= h_rhs.n_payloads) success = 0;
  return success;
}

/*
  Function: shunt_cs_comp_data_header
  compare two SHUNT data headers
  
  Parameters:
  h_lhs,h_rhs - two cs data headers
  n_payloads - number of data payloads
  Returns:
  success > 0
*/
int shunt_cs_comp_data_header (cs_data_header h_lhs,cs_data_header h_rhs,int n_payloads) {
  int success = 1;
  //compare
  if (h_lhs.data_type != h_rhs.data_type) success = 0;
  else {
    for(int i=0;i<n_payloads;i++) {
      if (h_lhs.trnx_payload_sizes[i] != h_rhs.trnx_payload_sizes[i]) success = 0;
    }
  }
  return success;
}
