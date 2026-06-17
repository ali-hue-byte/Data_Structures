typedef struct elem{
   char key[20];
   int value;
   struct elem *next;
}elem;

typedef struct {
    elem **pair;
    int size;
    int capacity;
}Hash_Table;

int Hash_function(const char *c, int capacity);
Hash_Table create_hash_table();
bool is_empty_hash_table(Hash_Table *h_t);
bool Key_in_Hash_Table(Hash_Table *h_t, const char *key);
void Hash_Table_add(Hash_Table *h_t, const char *key, int value);
int Hash_Table_get(Hash_Table *h_t, const char *key);
void Hash_Table_delete(Hash_Table *h_t, const char *key);
void Hash_Table_empty(Hash_Table *h_t);
void print_Hash_Table(Hash_Table *h_t);
int Hash_Table_size(Hash_Table *h_t);
void Hash_Table_update(Hash_Table *h_t, const char *key, int value);
