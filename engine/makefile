CC=gcc
CFLAGS= -Wall -O3
SRC=c
HDR=h
OBJ=o
BIN=exe

ENGN=engine

SRTS_DIR=./sorts
SWAP=$(SRTS_DIR)/swap
QUICK_SRT_M3=$(SRTS_DIR)/quick_sort_m3
QUICK_SRT_R=$(SRTS_DIR)/quick_sort_rand
QUICK3=$(SRTS_DIR)/quick3
DP_QUICK=$(SRTS_DIR)/dual_pivot_quicksort
TIM_SRT=$(SRTS_DIR)/tim_sort
MERGE_SRT=$(SRTS_DIR)/merge_sort
HEAP_SRT=$(SRTS_DIR)/heap_sort
SHELL_SRT=$(SRTS_DIR)/shell_sort
BIN_INS_SRT=$(SRTS_DIR)/binary_insertion_sort
INS_SRT=$(SRTS_DIR)/insertion_sort
COMB_SRT=$(SRTS_DIR)/comb_sort
CKTL_SRT=$(SRTS_DIR)/cocktail_sort
BUB_SRT=$(SRTS_DIR)/bubble_sort
SEL_SRT=$(SRTS_DIR)/selection_sort
CYC_SRT=$(SRTS_DIR)/cycle_sort
Q3_OPT_SRT=$(SRTS_DIR)/quick3_opt

ALL=$(ENGN).$(OBJ) $(SWAP).$(OBJ) $(INS_SRT).$(OBJ) $(BUB_SRT).$(OBJ) $(SEL_SRT).$(OBJ) $(HEAP_SRT).$(OBJ) 
ALL+=$(MERGE_SRT).$(OBJ) $(QUICK_SRT_M3).$(OBJ) $(QUICK_SRT_R).$(OBJ) $(SHELL_SRT).$(OBJ) $(TIM_SRT).$(OBJ) $(BIN_INS_SRT).$(OBJ)
ALL+=$(QUICK3).$(OBJ) $(DP_QUICK).$(OBJ) $(CKTL_SRT).$(OBJ) $(COMB_SRT).$(OBJ) $(CYC_SRT).$(OBJ) $(Q3_OPT_SRT).$(OBJ)

test: $(ALL)
	$(CC) $? -o $(ENGN).$(BIN) $(CFLAGS)

$(ENGN).$(OBJ): $(ENGN).$(SRC)
	$(CC) $< -c -o $@ $(CFLAGS)

$(SWAP).$(OBJ): $(SWAP).$(SRC)
	$(CC) $< -c -o $@ $(CFLAGS)

$(QUICK_SRT_M3).$(OBJ): $(QUICK_SRT_M3).$(SRC) $(QUICK_SRT_M3).$(HDR)
	$(CC) $< -c -o $@ $(CFLAGS)

$(QUICK_SRT_R).$(OBJ): $(QUICK_SRT_R).$(SRC) $(QUICK_SRT_R).$(HDR)
	$(CC) $< -c -o $@ $(CFLAGS)	
	
$(QUICK3).$(OBJ): $(QUICK3).$(SRC) $(QUICK3).$(HDR)
	$(CC) $< -c -o $@ $(CFLAGS)	

$(Q3_OPT_SRT).$(OBJ): $(Q3_OPT_SRT).$(SRC) $(Q3_OPT_SRT).$(HDR)
	$(CC) $< -c -o $@ $(CFLAGS)	
	
$(DP_QUICK).$(OBJ): $(DP_QUICK).$(SRC) $(DP_QUICK).$(HDR)
	$(CC) $< -c -o $@ $(CFLAGS)	
	
$(TIM_SRT).$(OBJ): $(TIM_SRT).$(SRC) $(TIM_SRT).$(HDR)
	$(CC) $< -c -o $@ $(CFLAGS)	
	
$(MERGE_SRT).$(OBJ): $(MERGE_SRT).$(SRC) $(MERGE_SRT).$(HDR)
	$(CC) $< -c -o $@ $(CFLAGS)
	
$(HEAP_SRT).$(OBJ): $(HEAP_SRT).$(SRC) $(HEAP_SRT).$(HDR)
	$(CC) $< -c -o $@ $(CFLAGS)
	
$(SHELL_SRT).$(OBJ): $(SHELL_SRT).$(SRC) $(SHELL_SRT).$(HDR)
	$(CC) $< -c -o $@ $(CFLAGS)
	
$(BIN_INS_SRT).$(OBJ): $(BIN_INS_SRT).$(SRC) $(BIN_INS_SRT).$(HDR)
	$(CC) $< -c -o $@ $(CFLAGS)
	
$(INS_SRT).$(OBJ): $(INS_SRT).$(SRC) $(INS_SRT).$(HDR)
	$(CC) $< -c -o $@ $(CFLAGS)

$(CKTL_SRT).$(OBJ): $(CKTL_SRT).$(SRC) $(CKTL_SRT).$(HDR)
	$(CC) $< -c -o $@ $(CFLAGS)

$(COMB_SRT).$(OBJ): $(COMB_SRT).$(SRC) $(COMB_SRT).$(HDR)
	$(CC) $< -c -o $@ $(CFLAGS)
	
$(BUB_SRT).$(OBJ): $(BUB_SRT).$(SRC) $(BUB_SRT).$(HDR)
	$(CC) $< -c -o $@ $(CFLAGS)

$(SEL_SRT).$(OBJ): $(SEL_SRT).$(SRC) $(SEL_SRT).$(HDR)
	$(CC) $< -c -o $@ $(CFLAGS)
	
$(CYC_SRT).$(OBJ): $(CYC_SRT).$(SRC) $(CYC_SRT).$(HDR)
	$(CC) $< -c -o $@ $(CFLAGS)
	
clean:
	rm *.$(OBJ)
	rm $(SRTS_DIR)/*.$(OBJ)
	rm *.$(BIN)