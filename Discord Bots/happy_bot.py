# simple discord bot to do some cool stuff!
# uses zenquotes.io api, openweathermap api
# bot says hello, inspirational quotes, encouragments, and weather updates

import discord
import requests
import random
import json

client = discord.Client()

sad_words = ['sad', 'upset', 'depressed', 'unhappy', 'angry', 'miserable', 'terrible', 'depressing', 'unfortunate', 'stress', 'hurt']
encouragements = [
    "Cheer up!",
    "Hang in there.",
    "You are a great person!",
    "Don't give up!",
    "Come on! You can do it!",
    "Optimism is the faith that leads to achievement."
]

def get_weather():
    response = requests.get("https://api.openweathermap.org/data/2.5/weather?q=LasVegas&units=imperial&appid=79a0b853c1ba460f96da8bcd75f7ce53")
    json_data = json.loads(response.text)   # translates api to json
    temp = json_data['main']['temp']
    # desc = json_data['weather']['main']
    city = json_data['name']
    weather = city + ': ' + str(temp) + ' °F'
    return(weather)

def get_quote():
    response = requests.get("https://zenquotes.io/api/random") # gets api
    json_data = json.loads(response.text)   # translates api to json
    quote = json_data[0]['q'] + ' -' + json_data[0]['a']
    return(quote)

@client.event
async def on_ready():
    print('We have logged in as {0.user}'.format(client))

@client.event
async def on_message(message):
    if message.author == client.user:
        return

    msg = message.content

    # bot says hello
    if message.content.startswith('$hello'):
        await message.channel.send("Hello")

    # bot says cool quote
    if message.content.startswith('$inspire'):
        quote = get_quote()
        await message.channel.send(quote)

    # bot cheers you up
    if any(word in msg for word in sad_words):
        await message.channel.send(random.choice(encouragements))
    
    # bot is weatherman
    if message.content.startswith('$weather'):
        current_weather = get_weather()
        await message.channel.send(current_weather)

client.run({TOKEN})
