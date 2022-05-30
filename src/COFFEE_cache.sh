valgrind --tool=cachegrind ./typical_col 2000 2000   >>COFFEE_cache.log
valgrind --tool=cachegrind ./typical_col 4000 4000   >>COFFEE_cache.log
valgrind --tool=cachegrind ./typical_col 6000 6000   >>COFFEE_cache.log
valgrind --tool=cachegrind ./typical_col 8000 8000   >>COFFEE_cache.log
valgrind --tool=cachegrind ./typical_col 10000 10000 >>COFFEE_cache.log
valgrind --tool=cachegrind ./typical_col 12000 12000 >>COFFEE_cache.log
valgrind --tool=cachegrind ./typical_col 14000 14000 >>COFFEE_cache.log
valgrind --tool=cachegrind ./typical_col 16000 16000 >>COFFEE_cache.log

valgrind --tool=cachegrind ./typical_+all 2000 2000   >>COFFEE_cache.log
valgrind --tool=cachegrind ./typical_+all 4000 4000   >>COFFEE_cache.log
valgrind --tool=cachegrind ./typical_+all 6000 6000   >>COFFEE_cache.log
valgrind --tool=cachegrind ./typical_+all 8000 8000   >>COFFEE_cache.log
valgrind --tool=cachegrind ./typical_+all 10000 10000 >>COFFEE_cache.log
valgrind --tool=cachegrind ./typical_+all 12000 12000 >>COFFEE_cache.log
valgrind --tool=cachegrind ./typical_+all 14000 14000 >>COFFEE_cache.log
valgrind --tool=cachegrind ./typical_+all 16000 16000 >>COFFEE_cache.log
