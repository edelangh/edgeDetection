#ifndef MLX_KEY_H
# define MLX_KEY_H

# ifdef __linux__
#  define KEY_ESCAPE 65307
#  define KEY_0 '0'
#  define KEY_1 '1'
#  define KEY_2 '2'
#  define KEY_3 '3'
#  define KEY_4 '4'
#  define KEY_5 '5'
#  define KEY_6 '6'
#  define KEY_7 '7'
#  define KEY_8 '8'
#  define KEY_9 '9'
# endif

# ifdef __APPLE__
#  define KEY_ESCAPE 53
#  define KEY_0 29
#  define KEY_1 18
#  define KEY_2 19
#  define KEY_3 20
#  define KEY_4 21
#  define KEY_5 23
#  define KEY_6 22
#  define KEY_7 26
#  define KEY_8 28
#  define KEY_9 25
# endif
#endif
