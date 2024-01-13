#include "stringslib.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

static void reverse(char s[]){
    int i, j;
    char c;
    for (i = 0, j = str_length(s)-1; i<j; i++, j--) {
       c = s[i];
       s[i] = s[j];
       s[j] = c;
     }
 }


size_t str_length(const char *str) {
  if (str == NULL){
    return 0;
  }
  else{
    size_t size = 0;
    while (str[size] != '\0'){
      ++size;
    }
    return size;
  }
}

int str_compare(const char *str1, const char *str2) {
  size_t i = 0;
  while (str1[i] != '\0' && str2[i] != '\0') {
    if (str1[i] != str2[i]) {
      return str1[i] - str2[i];
    }
    ++i;
  }
  return str1[i] - str2[i];
}

const char *str_search(const char *haystack, const char *needle) {
  size_t i = 0;
  while (haystack[i] != '\0') {
    size_t j = 0;
    while (needle[j] && haystack[i + j] && needle[j] == haystack[i + j]) {
      ++j;
    }
    if (needle[j] == '\0') {
      return haystack + i;
    }
    ++i;
  }
  return NULL;
}


const char *str_search_first_char(const char *haystack, char needle) {
  size_t i = 0;
  while (haystack[i] != '\0') {
    if (haystack[i] == needle) {
      return haystack + i;
    }
    ++i;
  }
  return NULL;
}


const char *str_search_last_char(const char *haystack, char needle) {
  size_t i = 0;
  const char *haystackTwo = haystack;
  while (haystack[i] != '\0') {
    if (haystack[i] == needle) {
      haystackTwo = haystack + i;
    }
    ++i;
  }
  if (haystackTwo != haystack){
    return haystackTwo;
  }
  return NULL;
}


size_t str_prefix_accept(const char *str, const char *chars) {
  int isOk = False;
  int i = 0;
  int j;
  size_t res = 0;
  while(str[i] != '\0'){
    j = 0;
    isOk = False;
    while (chars[j] != '\0'){
      if(chars[j] == str[i] && chars[j] != chars[j-1]){
        isOk = True;
        ++res;
      }
      ++j;
    }
    if (isOk == False){
      return res;
    }
    ++i
  }
  return res;
}

size_t str_prefix_reject(const char *str, const char *chars) {
  int i = 0;
  int j;
  size_t res = 0;
  while(str[i] != '\0'){
    j = 0;
    while(chars[j] != '\0'){
      if (str[i] == chars[j]){
        return res;
      }
      j++;
    }
    ++res;
    ++i;
  }
  return res;
}

int str_to_integer(const char *str) {
  int i = 0;
  int res = 0;

  while(str[i] != '\0'){
    if((str[i]<48)||(str[i]>57)){
      }
    else{
      res = res*10;
      res= res+(str[i]-48);
    }
    ++i;
  }
  return res;
}


int str_to_integer_ex(const char *str, const char **endptr, int base){
  int res = 0;
   size_t size = str_length(str);
   size_t i = 0;
   while(i < size){
     if((str[i] >= '0')&&(str[i] <= '9')&&(str[i] < base+'0')){
       res = str[i]-'0'+res*base;
     }
     else{
       if((base > 10)&&(str[i] >= 'a')&&(str[i]<='a'+base-10)){
         res = str[i]-'a'+10+res*base;
       }
       else{
         if((base > 10)&&(str[i] >= 'A')&&(str[i]<='A'+base-10)){
            res = str[i]-'A'+10+res*base;
          }
          else{
            if(((str[i] < '0')||(str[i] > '9')) && ((str[i] < 'A')|| (str[i] > 'A'+base-10)) && ((str[i] < 'a')||(str[i] > 'a'+base-10)))                   {
              break;
            }
          }
       }
     }
     ++i;
   }
   if(endptr){
       *endptr = &str[i];
   }
   return res;
}

void str_from_integer(char *dest, size_t size, int n) {
  size_t i = 0;
  char *memo = malloc(size);
  do {
      memo[i++] = n % 10 + '0';
  } while ((n /= 10) >0);
  memo[i] = '\0';
  reverse(memo);
  str_copy(dest, size, memo);
  free(memo);
}

void str_copy(char *dest, size_t size, const char *str) {
  size_t i = 0;
  while((str[i] != '\0')&&(i<size-1)){
    dest[i]=str[i];
    ++i;
  }
  dest[i] = '\0';
}

char *str_duplicate(const char *str) {
  size_t i = 0;
  size_t size = str_length(str);
  char *p = malloc(size);
  while(i<size){
    p[i]=str[i];
    ++i;
  }
  p[i] = '\0';
  return p;
}

void str_concat_string(char *dest, size_t size, const char *str) {
  size_t i = 0;
  size_t j = 0;
  while(dest[i] != '\0'){
    ++i;
  }
  while((i < size-1)&&(str[j] != '\0')){
    dest[i] = str[j];
    ++i;
    ++j;
  }
  dest[i] = '\0';
}

void str_concat_char(char *dest, size_t size, char c) {
  size_t i = 0;
  while(dest[i] != '\0'){
    ++i;
  }
  if(i<size-1){
    dest[i] = c;
    dest[i+1]= '\0';
  }
}

void str_concat_integer(char *dest, size_t size, int n) {
  char *memo = malloc(size);
  str_from_integer(memo,size,n);
  str_concat_string(dest,size,memo);
  free(memo);
}

void str_concat_array(char *dest, size_t size, const char *args[], char separator) {
  size_t i = 0;
  size_t j;
  size_t k = 0;
  while(dest[i] != '\0'){
    ++i;
  }
  if(args[k] != NULL){
    dest[i] = separator;
    ++i;
    while((args[k] != NULL)&&(i<size-1)){
      j = 0;
      while((args[k][j] != '\0')&&(i<size-1)){
        dest[i] = args[k][j];
        ++j;
        ++i;
      }
      if(args[k+1] != NULL){
        dest[i] = separator;
        ++i;
      }
      ++k;
    }
  }
  dest[i] = '\0';
}

char *str_join_string(const char *str1, const char *str2, char separator) {
  size_t i = 0;
  size_t j = 0;
  char *p = malloc((str_length(str1)+str_length(str1)+2));
  while(str1[i]!='\0'){
    p[i] = str1[i];
    ++i;
  }
  p[i] = separator;
  ++i;
  while (str2[j]!='\0') {
    p[i] = str2[j];
    ++i;
    ++j;
  }
  p[i] = '\0';
  return p;
}

static size_t sizeTab(const char *tab[]){
  size_t size = 0;
  size_t j;
  size_t k = 0;
  while(tab[k] != NULL){
    j = 0;
    while(tab[k][j] != '\0'){
      ++j;
      ++size;
    }
    ++size;
    ++k;
  }
  return size;
}

char *str_join_array(const char *args[], char separator) {
  char *res = malloc(sizeTab(args));
  size_t i = 0;
  size_t j;
  size_t k = 0;
  while(args[k] != NULL){
    j = 0;
    while(args[k][j] != '\0'){
      res[i] = args[k][j];
      ++j;
      ++i;
    }
    if(args[k+1] != NULL){
      res[i] = separator;
      ++i;
    }
    ++k;
  }
  res[i] = '\0';
  return res;
}
