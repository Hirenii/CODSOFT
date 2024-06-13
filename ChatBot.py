import re
import random

# For the inputs which are not predefined
def unknown():
    response = ["Could you please re-phrase it ?",
                "I am sorry, I didnot understand it !",
                " What does that mean ? "]

    return random.choice(response)

def msg_probability(user_msg,known_words,one_response=False,needed_words=[]):
    msg_certainity = 0
    has_needed_words = True

    # Counts how many words are present in each predefined message
    for word in user_msg:
        if word in known_words:
            msg_certainity +=1

    # Calculates the percent of known words in a user msg
    if len(known_words) > 0:
        percentage = float(msg_certainity) / float(len(known_words))
    else:
        percentage=0

    # Checks that the needed words are in the string
    for word in needed_words:
        if word not in user_msg:
            has_needed_words = False
            break
        
    if has_needed_words or one_response:
        return int(percentage*100)
    else:
        return 0

def check_all_msg(msg):
    highest_probability_list={}

    # Simplifies response creation
    def response(bot_response,list_of_words,one_response = False,needed_words =[]):
        nonlocal highest_probability_list
        highest_probability_list[bot_response] = msg_probability(msg,list_of_words,one_response,needed_words)

    # Response ---------------------------------------------------------------------------------------------------------------

    response('Hello',['hey','hello','hi'],one_response = True)
    response('I am doing fine !',['how','are','you','doing'],needed_words = ['how','doing'])
    response('GoodBye ! Have a nice day !',['bye','goodbye'],one_response = True)
    response('You\'re Welcome !',['thx','thanks'],one_response = True)
    response('I am a Chat-Bot.',['who','are','you'],needed_words = ['who','you'])
   
    best_match = max(highest_probability_list,key=highest_probability_list.get)

    return unknown() if highest_probability_list[best_match] < 1 else best_match

# Used to get the response
def get_response(user_input):
    split_msg = re.split(r'\s+|[,;?!.-]\s*',user_input.lower())
    response = check_all_msg(split_msg)
    return response

# Testing the response system
while True:
    print('Bot : '+ get_response(input('You : ')))