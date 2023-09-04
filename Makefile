#コンパイラ
CC=gcc
#コンパイルオプション
CFLAGS=-Wall -O2

#ターゲット名とソースファイル
TARGET=command.exe
SRC=main.c bm_search.c char_util.c tree.c word_processor.c

#オブジェクトファイル
OBJ=$(SRC:.c=.o)

#デフォルトのターゲット(all):プログラムをビルドする makeコマンドで実行される
all: $(TARGET)

#プログラムのビルドルール
$(TARGET):$(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

#オブジェクトファイルのビルドルール
%.o: %.c
	$(CC) $(CFLAGS) -c $<

#クリーンアップルール:中間ファイルの削除 make clean
clean:
	rm -f $(OBJ) $(TARGET)

