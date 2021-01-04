// sjlj2.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <coroutine>


//module test1;
//import MyFunc;

typedef enum {
	type_invalid = 0,
	type_uc8,
	type_sc8,
	type_us16,
	type_ss16,
	type_ui32,
	type_si32,
	type_ul64,
	type_sl64,
	type_ptr,
	type_msg,
	type_flt,
	type_dbl,
} value_type;

typedef union {
	unsigned char uc8;
	char sc8;
	unsigned short us16;
	short ss16;
	unsigned int ui32;
	int si32;
	unsigned long ul64;
	long sl64;
	void* ptr;
	char* msg;
	float flt;
	double dbl;
} element;

class vobj {
private:

	vobj* add(unsigned long value) {
		switch (this->type) {
		case type_msg:
			break;

		case type_uc8:
		case type_sc8:
			this->element.uc8 += (unsigned char)value;
			break;

		case type_us16:
		case type_ss16:
			this->element.us16 += (unsigned short)value;
			break;

		case type_ui32:
		case type_si32:
			this->element.ui32 += (unsigned int)value;
			break;

		case type_ul64:
		case type_sl64:
			this->element.ul64 += (unsigned long)value;
			break;

		case type_ptr:
			this->element.ptr = (void*)((size_t)(this->element.ptr) + (size_t)value);
			break;

		case type_flt:
			this->element.flt += (float)value;
			break;

		case type_dbl:
			this->element.dbl += (double)value;
			break;
		}
		return this;
	}

	vobj* sub(unsigned long value) {
		switch (this->type) {
		case type_msg:
			break;

		case type_uc8:
		case type_sc8:
			this->element.uc8 -= (unsigned char)value;
			break;

		case type_us16:
		case type_ss16:
			this->element.us16 -= (unsigned short)value;
			break;

		case type_ui32:
		case type_si32:
			this->element.ui32 -= (unsigned int)value;
			break;

		case type_ul64:
		case type_sl64:
			this->element.ul64 -= (unsigned long)value;
			break;

		case type_ptr:
			this->element.ptr = (void*)((size_t)(this->element.ptr) - (size_t)value);
			break;

		case type_flt:
			this->element.flt -= (float)value;
			break;

		case type_dbl:
			this->element.dbl -= (double)value;
			break;
		}
		return this;
	}

	vobj* mul(unsigned long value) {
		switch (this->type) {
		case type_msg:
			break;

		case type_uc8:
		case type_sc8:
			this->element.uc8 *= (unsigned char)value;
			break;

		case type_us16:
		case type_ss16:
			this->element.us16 *= (unsigned short)value;
			break;

		case type_ui32:
		case type_si32:
			this->element.ui32 *= (unsigned int)value;
			break;

		case type_ul64:
		case type_sl64:
			this->element.ul64 *= (unsigned long)value;
			break;

		case type_ptr:
			this->element.ptr = (void*)((size_t)(this->element.ptr) * (size_t)value);
			break;

		case type_flt:
			this->element.flt *= (float)value;
			break;

		case type_dbl:
			this->element.dbl *= (double)value;
			break;
		}
		return this;
	}

	vobj* div(unsigned long value) {
		switch (this->type) {
		case type_msg:
			break;

		case type_uc8:
		case type_sc8:
			this->element.uc8 /= (unsigned char)value;
			break;

		case type_us16:
		case type_ss16:
			this->element.us16 /= (unsigned short)value;
			break;

		case type_ui32:
		case type_si32:
			this->element.ui32 /= (unsigned int)value;
			break;

		case type_ul64:
		case type_sl64:
			this->element.ul64 /= (unsigned long)value;
			break;

		case type_ptr:
			this->element.ptr = (void*)((size_t)(this->element.ptr) / (size_t)value);
			break;

		case type_flt:
			this->element.flt /= (float)value;
			break;

		case type_dbl:
			this->element.dbl /= (double)value;
			break;
		}
		return this;
	}

	vobj* mod(unsigned long value) {
		switch (this->type) {
		case type_msg:
			break;

		case type_uc8:
		case type_sc8:
			this->element.uc8 %= (unsigned char)value;
			break;

		case type_us16:
		case type_ss16:
			this->element.us16 %= (unsigned short)value;
			break;

		case type_ui32:
		case type_si32:
			this->element.ui32 %= (unsigned int)value;
			break;

		case type_ul64:
		case type_sl64:
			this->element.ul64 %= (unsigned long)value;
			break;

		case type_ptr:
			this->element.ptr = (void*)((size_t)(this->element.ptr) % (size_t)value);
			break;

		case type_flt:
			//this->element.flt %= (float)value;
			break;

		case type_dbl:
			//this->element.dbl %= (double)value;
			break;
		}
		return this;
	}

public:
	int hash;
	value_type type;
	element element;

	void set_value(unsigned char uc8) {
		this->type = type_uc8;
		this->element.uc8 = uc8;
	}

	void set_value(char sc8) {
		this->type = type_sc8;
		this->element.sc8 = sc8;
	}

	void set_value(unsigned short us16) {
		this->type = type_us16;
		this->element.us16 = us16;
	}

	void set_value(short ss16) {
		this->type = type_ss16;
		this->element.ss16 = ss16;
	}

	void set_value(unsigned int ui32) {
		this->type = type_ui32;
		this->element.ui32 = ui32;
	}

	void set_value(int si32) {
		this->type = type_si32;
		this->element.si32 = si32;
	}

	void set_value(unsigned long ul64) {
		this->type = type_ul64;
		this->element.ul64 = ul64;
	}

	void set_value(long sl64) {
		this->type = type_sl64;
		this->element.sl64 = sl64;
	}

	void set_value(void* ptr) {
		this->type = type_ptr;
		this->element.ptr = ptr;
	}

	void set_value(char* msg) {
		this->type = type_msg;
		this->element.msg = msg;
	}

	void set_value(float flt) {
		this->type = type_flt;
		this->element.flt = flt;
	}

	void set_value(double dbl) {
		this->type = type_dbl;
		this->element.dbl = dbl;
	}

	vobj* operator +(unsigned char value) { return add(value); }
	vobj* operator +(char value) { return add(value); }
	vobj* operator +(unsigned short value) { return add(value); }
	vobj* operator +(short value) { return add(value); }
	vobj* operator +(unsigned int value) { return add(value); }
	vobj* operator +(int value) { return add(value); }
	vobj* operator +(unsigned long value) { return add(value); }
	vobj* operator +(long value) { return add(value); }
	vobj* operator +=(unsigned char value) { return add(value); }
	vobj* operator +=(char value) { return add(value); }
	vobj* operator +=(unsigned short value) { return add(value); }
	vobj* operator +=(short value) { return add(value); }
	vobj* operator +=(unsigned int value) { return add(value); }
	vobj* operator +=(int value) { return add(value); }
	vobj* operator +=(unsigned long value) { return add(value); }
	vobj* operator +=(long value) { return add(value); }

	vobj* operator -(unsigned char value) { return add(value); }
	vobj* operator -(char value) { return add(value); }
	vobj* operator -(unsigned short value) { return add(value); }
	vobj* operator -(short value) { return add(value); }
	vobj* operator -(unsigned int value) { return add(value); }
	vobj* operator -(int value) { return add(value); }
	vobj* operator -(unsigned long value) { return add(value); }
	vobj* operator -(long value) { return add(value); }
	vobj* operator -=(unsigned char value) { return add(value); }
	vobj* operator -=(char value) { return add(value); }
	vobj* operator -=(unsigned short value) { return add(value); }
	vobj* operator -=(short value) { return add(value); }
	vobj* operator -=(unsigned int value) { return add(value); }
	vobj* operator -=(int value) { return add(value); }
	vobj* operator -=(unsigned long value) { return add(value); }
	vobj* operator -=(long value) { return add(value); }

	vobj* operator *(unsigned char value) { return add(value); }
	vobj* operator *(char value) { return add(value); }
	vobj* operator *(unsigned short value) { return add(value); }
	vobj* operator *(short value) { return add(value); }
	vobj* operator *(unsigned int value) { return add(value); }
	vobj* operator *(int value) { return add(value); }
	vobj* operator *(unsigned long value) { return add(value); }
	vobj* operator *(long value) { return add(value); }
	vobj* operator *=(unsigned char value) { return add(value); }
	vobj* operator *=(char value) { return add(value); }
	vobj* operator *=(unsigned short value) { return add(value); }
	vobj* operator *=(short value) { return add(value); }
	vobj* operator *=(unsigned int value) { return add(value); }
	vobj* operator *=(int value) { return add(value); }
	vobj* operator *=(unsigned long value) { return add(value); }
	vobj* operator *=(long value) { return add(value); }

	vobj* operator /(unsigned char value) { return add(value); }
	vobj* operator /(char value) { return add(value); }
	vobj* operator /(unsigned short value) { return add(value); }
	vobj* operator /(short value) { return add(value); }
	vobj* operator /(unsigned int value) { return add(value); }
	vobj* operator /(int value) { return add(value); }
	vobj* operator /(unsigned long value) { return add(value); }
	vobj* operator /(long value) { return add(value); }
	vobj* operator /=(unsigned char value) { return add(value); }
	vobj* operator /=(char value) { return add(value); }
	vobj* operator /=(unsigned short value) { return add(value); }
	vobj* operator /=(short value) { return add(value); }
	vobj* operator /=(unsigned int value) { return add(value); }
	vobj* operator /=(int value) { return add(value); }
	vobj* operator /=(unsigned long value) { return add(value); }
	vobj* operator /=(long value) { return add(value); }

	vobj* operator %(unsigned char value) { return add(value); }
	vobj* operator %(char value) { return add(value); }
	vobj* operator %(unsigned short value) { return add(value); }
	vobj* operator %(short value) { return add(value); }
	vobj* operator %(unsigned int value) { return add(value); }
	vobj* operator %(int value) { return add(value); }
	vobj* operator %(unsigned long value) { return add(value); }
	vobj* operator %(long value) { return add(value); }
	vobj* operator %=(unsigned char value) { return add(value); }
	vobj* operator %=(char value) { return add(value); }
	vobj* operator %=(unsigned short value) { return add(value); }
	vobj* operator %=(short value) { return add(value); }
	vobj* operator %=(unsigned int value) { return add(value); }
	vobj* operator %=(int value) { return add(value); }
	vobj* operator %=(unsigned long value) { return add(value); }
	vobj* operator %=(long value) { return add(value); }
};

typedef struct {
	vobj* key;
	vobj* val;
} vpair;

class dic {
private:
	vpair* pairs;
	int last;
	int length;

public:
	dic(int length) {
		this->pairs = (vpair*)malloc(sizeof(dic) * length);
		this->last = 0;
		this->length = length;
	}

	vpair* get_pair(vobj* key) {
		vpair* end = &pairs[length];		
		for (vpair* cur = pairs; cur < end; cur++) {
			if (cur->key->hash == key->hash)
				return cur;
		}
		return NULL;
	}

	vobj* get_value(vobj* key) {
		vpair* pair = get_pair(key);
		return (NULL == pair) ? NULL : pair->val;
	}

	void set_pair(vobj* key, vobj* val) {
		vpair* pair = get_pair(key);
		if (NULL == pair) {
			vpair* cur = &this->pairs[last++];
			cur->key = key;
			cur->val = val;
		}
	}

};

class queue {
private:
	vobj** arr;
	int length;
	int first;
	int last;

public:
	queue(int length) {
		this->arr = new vobj*[length];
		this->length = length;
		this->first = 0;
		this->last = 0;
	}

	~queue() {
		if (NULL != arr) {
			delete this->arr;
			arr = NULL;
		}
	}

	bool try_enque(vobj* value) {
		int next = (this->last + 1) % this->length;
		if (this->first == next)
			return false;

		this->arr[this->last] = value;
		this->last = next;
		return true;
	}

	bool try_dequeue(vobj** result) {
		if (this->first == this->last)
			return false;

		*result = this->arr[this->first];
		this->first = (this->first + 1) % this->length;
		return true;
	}
};




int main()
{
	queue* que = new queue(10);

	vobj v1 = { .hash = 0, .type = type_invalid };
	vobj v2 = { .hash = 0, .type = type_invalid };
	v1.set_value(1234);
	v2.set_value(4321);

	que->try_enque(&v1);
	que->try_enque(&v2);

	vobj* a1;
	vobj* a2;

	que->try_dequeue(&a1);
	que->try_dequeue(&a2);

	v1 += 50000;

	printf("a1=%d\n", a1->element.ui32);
	printf("a2=%d\n", a2->element.ui32);
}






// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
