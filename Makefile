# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssukhova <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/15 15:40:53 by ssukhova          #+#    #+#              #
#    Updated: 2024/03/22 17:22:12 by ssukhova         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= .minitalk
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror
INC_DIR		=  ./lib/libft/include
BUILD_DIR	=  out
BIN_DIR		=  $(BUILD_DIR)/exec
OBJ_DIR		=  $(BUILD_DIR)/obj
SRC_DIR		=  src
LIBFT_PATH	=  ./lib/libft
LIBFT		=  $(LIBFT_PATH)/libft.a
INCLUDES	:= -I. -I $(INC_DIR)
CFLAGS		+= $(INCLUDES)
LINK_FLAGS	:= -L $(LIBFT_PATH) -lft
EXECS		= client server
RM 			:= rm -rf

client_SRCS =  $(SRC_DIR)/client.c
client_OBJS =  $(client_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

server_SRCS =  $(SRC_DIR)/server.c
server_OBJS =  $(server_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

client_bonus_SRCS = $(SRC_DIR)/client_bonus.c $(SRC_DIR)/struct_bonus.c
client_bonus_OBJS = $(client_bonus_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

server_bonus_SRCS = $(SRC_DIR)/server_bonus.c $(SRC_DIR)/struct_bonus.c
server_bonus_OBJS = $(server_bonus_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(LIBFT) $(BIN_DIR)/client $(BIN_DIR)/server

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/client: $(client_OBJS) $(LIBFT)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ $^ $(LINK_FLAGS)

$(BIN_DIR)/server: $(server_OBJS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ $^ $(LINK_FLAGS)

$(LIBFT):
	make -C $(LIBFT_PATH)

bonus: $(LIBFT) $(BIN_DIR)/client $(BIN_DIR)/server

clean:
	$(RM) $(OBJ_DIR)
	make -C $(LIBFT_PATH) clean

fclean: clean
	$(RM) $(BIN_DIR)
	make -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re
