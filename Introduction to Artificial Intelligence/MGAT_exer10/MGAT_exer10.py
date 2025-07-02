'''
CMSC 170: Introduction to Artificial Intelligence
Exercise 10: Designing an AI Agent for a Tic-Tac-Toe Game

MARY GWYNETH A. TOLENTINO
2021-02990
CMSC 170 GH-5L
'''

import pygame
import time 

# Initialize pygame
pygame.init()       
pygame.display.set_caption("Tic-Tac-Toe Game")
screen = pygame.display.set_mode((900,900)) # set screen size to 900 x 900    
white = [255, 255, 255]
screen.fill(white)      

# Load and resize images for the board and buttons
size = 300      # size of the tiles 
h, w = 200, 90  # button dimensions
tile = pygame.image.load("./img/tile.JPG")          
tile = pygame.transform.scale(tile, (size, size))
x = pygame.image.load("./img/x.jpg")
x = pygame.transform.scale(x, (size, size))
o = pygame.image.load("./img/o.jpg")
o = pygame.transform.scale(o, (size, size))
x2 = pygame.image.load("./img/x2.jpg")
x_button = pygame.transform.scale(x2, (h, w))
o2 = pygame.image.load("./img/o2.jpg")
o_button = pygame.transform.scale(o2, (h, w))
exit = pygame.image.load("./img/exit.jpg")
exit_button = pygame.transform.scale(exit, (h, w))
ok = pygame.image.load("./img/ok.jpg")
ok_button = pygame.transform.scale(ok, (h, w))

# Lists and variables for game logic
menu_buttons = [x_button, o_button, exit_button]    # list of buttons for menu
button_positions = []   # position list for buttons in the menu

# Initial blank Tic-Tac-Toe board
board_state = [['', '', ''], ['', '', ''], ['', '', '']] 

# Draw the menu
def draw_menu():         
    x_position = 140
    font_name = pygame.font.match_font('ubuntumono') 
    main_font = pygame.font.Font('freesansbold.ttf', 60)
    sub_font = pygame.font.Font(font_name, 40)
    
    # Render texts
    main_text = "How do you want to play?"
    text = main_font.render(main_text, True, (0, 0, 0))
    text_rect = text.get_rect(center=(450, 200))
    screen.blit(text, text_rect)

    sub_text_line1 = "X - You play first"
    sub_text_line2 = "O - AI plays first"
    sub_text1 = sub_font.render(sub_text_line1, True, (255, 0, 0))
    sub_text2 = sub_font.render(sub_text_line2, True, (0, 0, 255))
    sub_text1_rect = sub_text1.get_rect(center=(450, 270))  
    sub_text2_rect = sub_text2.get_rect(center=(450, 310))  
    screen.blit(sub_text1, sub_text1_rect)
    screen.blit(sub_text2, sub_text2_rect)
    
    for i in menu_buttons:            
        screen.blit(i, (x_position,500))
        button_positions.append(x_position)
        x_position = x_position + h + 10    # set the x coordinates for the buttons

# Draw the board
def draw_board():        
    y_position = 0
    for i in range(3):
        x_position = 0
        for j in range(3):
            screen.blit(tile, (x_position, y_position))
            x_position += 300   # x coord is incremented by 300 since side of tile is 300
        y_position += 300       # y coord is incremented by 300 since side of tile is 300

# Draw the game over menu
def draw_game_over(status):        
    if status == 'AIwin':       # Display if Ai won
        font = pygame.font.Font('freesansbold.ttf', 50)
        text = font.render("You Lost!", True, (0, 0, 0))
        text_rect = text.get_rect()
        text_rect.center = (450, 200)
        screen.blit(text, text_rect)
    if status == 'Playerwin':    # Display if player won *IMPOSSIBLE HEHEW 
        font = pygame.font.Font('freesansbold.ttf', 50)
        text = font.render("You Won!", True, (0, 0, 0))
        text_rect = text.get_rect()
        text_rect.center = (450, 200)
        screen.blit(text, text_rect)
    if status == 'Draw':         # Display if draw
        font = pygame.font.Font('freesansbold.ttf', 50)
        text = font.render("It's a Draw!", True, (0, 0, 0))
        text_rect = text.get_rect()
        text_rect.center = (450, 200)
        screen.blit(text, text_rect)
    screen.blit(ok_button, (350,500))

def is_terminal(board): # returns true if state of game board is terminal
    # Check if AI has winning conditions
    for i in range(len(board)):
        row_checker = 0
        for j in range(len(board)):
            if board[i][j]==AI_symbol:
                row_checker += 1
        if row_checker==3:     #check row if full of AI's markers (either x or o)
            return (True, 'AIwin')
    for i in range(len(board)):
        col_checker = 0
        for j in range(len(board)):
            if board[j][i]==AI_symbol:
                col_checker += 1
        if col_checker==3:     #check column if full of AI's markers (either x or o)
            return (True, 'AIwin')
    if board[0][0]==AI_symbol and board[1][1]==AI_symbol and board[2][2]==AI_symbol:
        return (True, 'AIwin')
    if board[0][2]==AI_symbol and board[1][1]==AI_symbol and board[2][0]==AI_symbol:
        return (True, 'AIwin')
        
    # Check if player has winning conditions
    for i in range(len(board)):         
        row_checker = 0
        for j in range(len(board)):
            if board[i][j]==player_symbol:
                row_checker += 1
        if row_checker==3:     #check row if full of player's markers (either x or o)
            return (True, 'Playerwin')
    for i in range(len(board)):
        col_checker = 0
        for j in range(len(board)):
            if board[j][i]==player_symbol:
                col_checker += 1
        if col_checker==3:     #check column if full of player's markers (either x or o)
            return (True, 'Playerwin')
    if board[0][0]==player_symbol and board[1][1]==player_symbol and board[2][2]==player_symbol:
        return (True, 'Playerwin')
    if board[0][2]==player_symbol and board[1][1]==player_symbol and board[2][0]==player_symbol:
        return (True, 'Playerwin')

    full_board = 0
    for i in range(len(board)): # check if board is full (meaning it is a draw)
        for j in range(len(board)):
            if board[i][j] != '':
                full_board += 1
    if full_board == 9:
        return (True, 'Draw')
    else:
        return (False, None)

def utility(board):     # returns 1 if AI wins, -1 if player wins, and 0 if draw
    # Check if AI has winning conditions
    for i in range(len(board)):
        row_checker = 0
        for j in range(len(board)):
            if board[i][j]==AI_symbol:
                row_checker += 1
        if row_checker==3:     
            return 1
    for i in range(len(board)):
        col_checker = 0
        for j in range(len(board)):
            if board[j][i]==AI_symbol:
                col_checker += 1
        if col_checker==3:     
            return 1
    if board[0][0]==AI_symbol and board[1][1]==AI_symbol and board[2][2]==AI_symbol:
        return 1
    if board[0][2]==AI_symbol and board[1][1]==AI_symbol and board[2][0]==AI_symbol:
        return 1

    # Check if player has winning conditions
    for i in range(len(board)):         
        row_checker = 0
        for j in range(len(board)):
            if board[i][j]==player_symbol:
                row_checker += 1
        if row_checker==3:     
            return -1
    for i in range(len(board)):
        col_checker = 0
        for j in range(len(board)):
            if board[j][i]==player_symbol:
                col_checker += 1
        if col_checker==3:     
            return -1
    if board[0][0]==player_symbol and board[1][1]==player_symbol and board[2][2]==player_symbol:
        return -1
    if board[0][2]==player_symbol and board[1][1]==player_symbol and board[2][0]==player_symbol:
        return -1
    return 0    # game is draw

def action(board):      
    actions = []        
    for i in range(len(board)):
        for j in range(len(board)):
            if board[i][j] == '':       # check if player can still mark an X or O in a tile
                actions.append((i,j))
    return actions      # list of possible actions that can be performed on the current state of the board

# Max value is for the AI's moves since we want AI to always win (or at least draw)
def max_value(board):       
    m = float('-inf')  # negative infinity for max value 
    action_list = action(board)
    for i in range(len(action_list)):
        board[action_list[i][0]][action_list[i][1]] = AI_symbol # peform the action in actionlist
        v = value(board, 'human')   # pass 'human' to value, since AI is done taking its turn
        if m < v[0]: 
            m = v[0]        
            best_action = action_list[i]                    # keep the best_action from action_list
        board[action_list[i][0]][action_list[i][1]] = ''    # set the board_state's tile to '', basically undoing the action performed in line 211
    return (m, best_action)

def min_value(board):   # for the player's move
    m = float('inf')    # positive infinity for min value
    action_list = action(board)
    for i in range(len(action_list)):
        board[action_list[i][0]][action_list[i][1]] = player_symbol
        v = value(board, 'AI')      # pass 'AI', since human is done taking its turn
        if m > v[0]:
            m = v[0]
            best_action = action_list[i]
        board[action_list[i][0]][action_list[i][1]] = ''
    return (m, best_action)

# Get the best action the AI can perform by looking at the current state and every possible state until it reaches a terminal state
def value(board, player):       
    terminal = is_terminal(board)
    if terminal[0] is True:        # get the boolean value at index 0, since is_terminal returns a tuple
        return (utility(board), None)
    if player == 'AI':      # max node 
        return max_value(board)
    if player == 'human':   # min node, since we don't want player to win
        return min_value(board)

# Main function to execute the Tic-Tac-Toe game
def main():
    draw_menu()
    pygame.display.flip()
    menu_active = True          # flag to keep the menu active until the user makes a choice
    game_active = False         # flag to indicate whether the game loop is active until we reach a terminal state
    game_over_screen = False    # flag to indicate whether the game over screen is displayed
    GAME_OVER = (False, None)   # Initialize GAME_OVER as a tuple
    
    while menu_active:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                menu_active = False
            if event.type == pygame.MOUSEBUTTONDOWN:
                mouse_pos = pygame.mouse.get_pos()
                for i in range(len(menu_buttons)):
                    if x_button.get_rect(topleft=(button_positions[0],500)).collidepoint(mouse_pos):        # when user chooses to be X
                        Player_X = True     # User will play as X
                        game_active = True  # start the game
                        menu_active = False # exit the menu loop
                    if o_button.get_rect(topleft=(button_positions[1],500)).collidepoint(mouse_pos):        # when user chooses to be O
                        Player_X = False    # User will play as O
                        game_active = True  # start the game
                        menu_active = False # exit the menu loop
                    if exit_button.get_rect(topleft=(button_positions[2],500)).collidepoint(mouse_pos):     # when user chooses to exit
                        menu_active = False
        pygame.display.update()

    if game_active is True:
        screen.fill(white)              # fill the screen white basically clearing the menu
        draw_board()                    # draw the game board
        global player_symbol, AI_symbol # markers
        t1, t2, t3, t4, t5, t6, t7, t8, t9 = False, False, False, False, False, False, False, False, False  # boolean values for each tile
        # Determine player and AI symbols based on the user's choice
        if Player_X==True:       
            mark_player = x     # Player's marker is X
            mark_AI = o         # AI's marker is O
            player_symbol = 'x'
            AI_symbol = 'o'
            player_turn = True  # Player goes first
        else:
            mark_player = o     # Player's marker is o
            mark_AI = x         # AI's marker is x
            player_symbol = 'o'
            AI_symbol = 'x'
            # AI makes the first move by placing its marker at the top-left corner
            screen.blit(mark_AI, (0, 0))
            board_state[0][0] = AI_symbol  # Update the board state
            player_turn = True  # Player's turn after AI's move
            t1 = True           # Mark the top-left tile as occupied

    # MAIN GAME LOOP
    while game_active is True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                game_active = False
            if event.type == pygame.MOUSEBUTTONDOWN:
                mouse_pos = pygame.mouse.get_pos()
                # Handle player's moves for each tile
                if tile.get_rect(topleft=(0, 0)).collidepoint(mouse_pos) and player_turn is True: 
                    if t1 is False:     # if tile is False, it means it is still empty
                        screen.blit(mark_player, (0,0))     # draw player's marker on the tile (x or o)
                        t1 = True       # mark the tile as occupied
                        board_state[0][0] = player_symbol   # update the board state
                        player_turn = False # AI's turn
                if tile.get_rect(topleft=(300, 0)).collidepoint(mouse_pos) and player_turn is True:
                    if t2 is False:
                        screen.blit(mark_player, (300,0))
                        t2 = True
                        board_state[0][1] = player_symbol   
                        player_turn = False
                if tile.get_rect(topleft=(600, 0)).collidepoint(mouse_pos) and player_turn is True:
                    if t3 is False:
                        screen.blit(mark_player, (600,0))
                        t3 = True
                        board_state[0][2] = player_symbol
                        player_turn = False
                if tile.get_rect(topleft=(0, 300)).collidepoint(mouse_pos) and player_turn is True:
                    if t4 is False:
                        screen.blit(mark_player, (0, 300))
                        t4 = True
                        board_state[1][0] = player_symbol
                        player_turn = False
                if tile.get_rect(topleft=(300, 300)).collidepoint(mouse_pos) and player_turn is True:
                    if t5 is False:
                        screen.blit(mark_player, (300, 300))
                        t5 = True   
                        board_state[1][1] = player_symbol
                        player_turn = False
                if tile.get_rect(topleft=(600, 300)).collidepoint(mouse_pos) and player_turn is True:
                    if t6 is False:
                        screen.blit(mark_player, (600, 300))
                        t6 = True
                        board_state[1][2] = player_symbol
                        player_turn = False
                if tile.get_rect(topleft=(0, 600)).collidepoint(mouse_pos) and player_turn is True:
                    if t7 is False:
                        screen.blit(mark_player, (0, 600))
                        t7 = True
                        board_state[2][0] = player_symbol
                        player_turn = False
                if tile.get_rect(topleft=(300, 600)).collidepoint(mouse_pos) and player_turn is True:
                    if t8 is False:
                        screen.blit(mark_player, (300, 600))
                        t8 = True   
                        board_state[2][1] = player_symbol
                        player_turn = False
                if tile.get_rect(topleft=(600, 600)).collidepoint(mouse_pos) and player_turn is True:
                    if t9 is False:
                        screen.blit(mark_player, (600, 600))
                        t9 = True
                        board_state[2][2] = player_symbol
                        player_turn = False
                # Check if the game is over
                GAME_OVER = is_terminal(board_state)        
                if GAME_OVER[0] is True:    # check if game is in a terminal state
                    game_active = False     # exit the current while loop
                    game_over_screen = True # display the game over screen

                # AI's turn if the game is not over and it's the AI's turn.
                if player_turn is False and game_active is True: 
                    AI = value(board_state, 'AI')     # get the AI's best action using Minimax
                    # AI makes its move based on the calculated best action
                    if AI[1][0] == 0 and AI[1][1] == 0 and t1 is False:     
                        screen.blit(mark_AI, (0, 0))
                        board_state[0][0] = AI_symbol     
                        player_turn = True  # Player's turn
                        t1 = True
                    if AI[1][0] == 0 and AI[1][1] == 1 and t2 is False:
                        screen.blit(mark_AI, (300, 0))
                        board_state[0][1] = AI_symbol
                        player_turn = True
                        t2 = True
                    if AI[1][0] == 0 and AI[1][1] == 2 and t3 is False:
                        screen.blit(mark_AI, (600, 0))
                        board_state[0][2] = AI_symbol
                        player_turn = True
                        t3 = True
                    if AI[1][0] == 1 and AI[1][1] == 0 and t4 is False:
                        screen.blit(mark_AI, (0, 300))
                        board_state[1][0] = AI_symbol
                        player_turn = True
                        t4 = True
                    if AI[1][0] == 1 and AI[1][1] == 1 and t5 is False:
                        screen.blit(mark_AI, (300, 300))
                        board_state[1][1] = AI_symbol
                        player_turn = True
                        t5 = True
                    if AI[1][0] == 1 and AI[1][1] == 2 and t6 is False:
                        screen.blit(mark_AI, (600, 300))
                        board_state[1][2] = AI_symbol
                        player_turn = True
                        t6 = True
                    if AI[1][0] == 2 and AI[1][1] == 0 and t7 is False:
                        screen.blit(mark_AI, (0, 600))
                        board_state[2][0] = AI_symbol
                        player_turn = True
                        t7 = True
                    if AI[1][0] == 2 and AI[1][1] == 1 and t8 is False:
                        screen.blit(mark_AI, (300, 600))
                        board_state[2][1] = AI_symbol
                        player_turn = True
                        t8 = True
                    if AI[1][0] == 2 and AI[1][1] == 2 and t9 is False:
                        screen.blit(mark_AI, (600, 600))
                        board_state[2][2] = AI_symbol
                        player_turn = True
                        t9 = True
                GAME_OVER = is_terminal(board_state)
                if GAME_OVER[0] is True:
                    game_active = False
                    game_over_screen = True
        pygame.display.update()

    # GAME OVER SEQUENCE
    screen.fill(white)              # clear the screen
    draw_game_over(GAME_OVER[1])    # display game over menu and text with the result
    time.sleep(0.5)       

    while game_over_screen is True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                game_over_screen = False
            if event.type == pygame.MOUSEBUTTONDOWN:
                mouse_pos = pygame.mouse.get_pos()
                if ok_button.get_rect(topleft=(350, 500)).collidepoint(mouse_pos):  # ok button or exit button
                    game_over_screen = False
        pygame.display.update()

main()