# philosophers
# for 42tokyo

#　課題内容
「食事する哲学者の問題」に似た問題。
以下のルールの下、行動する哲学者たちを並列処理、排他制御を使い、


# ルール
食事 → 睡眠 → 思考  
食事：2本のフォークを持って食事する  
睡眠：フォークを落として眠る  
思考：フォークを手に取る  


# 使用可能関数
memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock

# 使い方

実行ファイル名 philo(makeで作成可能)。

引数で以下の情報を与える  
・哲学者の人数 (=フォークの数)  
・死ぬまでの時間 (ms)  
・食事する時間 (ms)  
・睡眠する時間 (ms)  
オプション引数  
・プログラムを終了する食事回数  

例：./philo 3 600 300 400

