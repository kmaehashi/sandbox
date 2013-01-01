#include <stdio.h>
#include <senna/senna.h>

int main() {
	sen_rc status;
	sen_index *index;
	sen_records records;

	status = sen_init();

	index = sen_index_create("test-index/test", 0, SEN_INDEX_NGRAM, 10, sen_enc_utf8);

	if (index == NULL) {
		printf("index is NULL!!\n");
	} else {
		printf("OK\n");
	}

	status = sen_index_upd(index, "foo", NULL, 0, "Hello World!", 12);
	status = sen_index_upd(index, "bar", NULL, 0, "Hello World 2!", 14);
	status = sen_index_upd(index, "hoge", NULL, 0, "Hello World 3!", 14);

	records = sen_index_sel(index, "bar", 3);


	status = sen_fin();
	return 0;
}

