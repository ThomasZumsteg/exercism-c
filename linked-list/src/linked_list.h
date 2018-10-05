typedef int ll_data_t;
struct list_item;

struct list_item** new_list();

void delete_list(struct list_item**);

int is_list_empty(struct list_item**);

int push(struct list_item**, ll_data_t);
int unshift(struct list_item**, ll_data_t);

ll_data_t pop(struct list_item**);
ll_data_t shift(struct list_item**);
