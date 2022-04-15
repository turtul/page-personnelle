import os
import random
import discord
import time
from discord.ext import commands, tasks
from dotenv import load_dotenv

load_dotenv(dotenv_path="config")

help_command = commands.DefaultHelpCommand(
    no_category='Commandes'
)

intents = discord.Intents().all()

bot = commands.Bot(command_prefix="<", help_command=help_command, intents=intents,
                   description="Le larbin de la Meat.Inc")

listeActivite = ["Lawrise, va bosser !", "être beau", "manger de la viande", "https://bit.ly/3q77nst", "taper <help"]


# comment on fait pour envoyer un msg dans un salon spécifique
# critique: discord.TextChannel = bot.get_channel(812441550104559647)
# await critique.send(content=f"MeatBot est connecté !")

@bot.event
async def on_ready():
    print("Le bot est co")
    changeActivity.start()


@bot.event
async def on_message(message):
    await bot.process_commands(message)
    if message.content.lower().endswith("quoi") or message.content.lower().endswith(
            "quoi ?") or message.content.lower().endswith("quoi !"):
        await message.channel.send("feur")
    elif message.content.lower().endswith("nez") or message.content.lower().endswith("né"):
        await message.channel.send("gro")


@tasks.loop(seconds=30.0)
async def changeActivity():
    indActivite = random.randint(0, len(listeActivite) - 1)
    await bot.change_presence(activity=discord.Game(name=listeActivite[indActivite]))


@bot.event
async def on_voice_state_update(ctx, vcBefore, vcAfter):
    if vcAfter.channel is bot.get_channel(954498113987555338):
        if ctx == bot.get_user(537736960630980629):
            await bot.get_channel(763436496823779397).send(
                f"{ctx.mention} bon jembé tu vas bouger ton gros fiak et dégager du voc !")
        else:
            await bot.get_channel(763436496823779397).send(f"{ctx.mention} pfff apprend à cliquer sur raccrocher stp.")
    if vcBefore.channel is bot.get_channel(954498113987555338):
        await bot.get_channel(763436496823779397).send(f"{ctx.mention} voilà je préfère ça.")


@bot.event
async def on_message_edit(msgBefore, msgAfter):
    await msgBefore.reply(f"Pourquoi tu as changé ton message moi je l'aimais bien comme ça : \n> {msgBefore.content}")


"""
@bot.event
async def on_member_update(memberBefore, memberAfter):
    if memberAfter.activity:
        if memberAfter.activity.name == "VALORANT":
            await bot.get_channel(937078462005534730).send(f"{memberAfter.mention} arretes un peu de jouer à Valorant, fait un truc mieux non ? reprend ta vie en main stp.")
    if memberBefore.activity:
        if memberBefore.activity.name == "VALORANT":
            await bot.get_channel(937078462005534730).send(f"{memberBefore.mention} voilà tu as pris la bonne décision.")
"""


@bot.command(name='play', description='Je me transforme en lecteur mp3 (il faut mettre le volume en argument (%age)).',
             pass_context=True)
async def play(ctx, volume: int):
    user = ctx.message.author
    volume = volume / 100
    if user.voice.channel is not None:
        salonVocal = user.voice.channel
        # on regarde si le bot à dejà des instance de vocal
        if ctx.bot.voice_clients:
            # si il en a alors on attribue la premiere instance (on suppose que c'est la bonne pck nrml c la seul) et on l'attribue a vc
            vc = ctx.bot.voice_clients[0]
        else:
            vc = await salonVocal.connect()
        # vieux moeyn de crer une source : source = await discord.FFmpegPCMAudio.from_probe("testing.mp3", method='fallback')
        sourceMusic = discord.FFmpegPCMAudio("testing.mp3")
        vc.play(sourceMusic)
        vc.source = discord.PCMVolumeTransformer(vc.source)
        vc.source.volume = volume
    else:
        await ctx.send.say('Tu doits rejoindre un channel vocal pour lancer cette commande.')


@bot.command(name='player', description="Donne moi un ordre à executer (il faut mettre le mettre en argument)",
             pass_context=True)
async def player(ctx, action):
    if ctx.bot.voice_clients:
        # si il en a alors on attribue la premiere instance (on suppose que c'est la bonne pck nrml c la seul) et on l'attribue a vc
        vc = ctx.bot.voice_clients[0]
        source = ctx.guild.voice_client.source
        volume = source.volume
        if action == "stop":
            vc.stop()
        elif action == "pause":
            vc.pause()
        elif action == "resume":
            vc.resume()
        elif action == "volup":
            if volume + 0.1 <= 1:
                vol = volume + 0.1
                source.volume = vol
            else:
                source.volume = 1
                await ctx.send("Le volume est déjà au max !")
        elif action == "voldown":
            if volume - 0.1 >= 0:
                vol = volume - 0.1
                source.volume = vol
            else:
                source.volume = 0
                await ctx.send("Le volume est déjà au minimum !")
        else:
            await ctx.send("Cette commande n'existe pas.")
    else:
        await ctx.send("Je ne suis pas connecté à un salon vocal.")


@bot.command(name="viensVoc", description="Je te rejoins en voc.")
async def viensVoc(ctx):
    connected = ctx.author.voice
    if connected:
        await connected.channel.connect()
    else:
        await ctx.send("Rejoins d'abord un channel vocal.")


@bot.command(name="bougeDuVoc", description="Tu veux vraiment que je parte ? :,( .")
async def bougeDuVoc(ctx):
    if ctx.bot.voice_clients:
        await ctx.voice_client.disconnect()
    else:
        await ctx.send("Je ne suis pas connecté dans un channel vocal")


@bot.command(name="jeVeuxEtre", description="Je t'ajoute le role de ton choix (passé en argument).")
async def jeVeuxEtre(ctx, *role):
    try:
        if isAdmin(ctx) or ctx.author.name == "Meatman":
            texteListe = []
            texte = ""
            for j in range(len(role)):
                texteListe.append(role[j])
            for mot in texteListe:
                texte = texte + mot + " "
            texte = texte[:len(texte) - 1]
            role_a_donne = discord.utils.get(ctx.guild.roles, name=f"{texte}")
            if role_a_donne:
                await ctx.author.add_roles(role_a_donne)
                await ctx.send(f"Tu es désormais un **{role_a_donne}**.")
            else:
                await ctx.send("Ce rôle n'existe pas.")
        else:
            await ctx.send("Tu es trop faible pour utiliser cette commande.")
    except discord.errors.Forbidden:
        await ctx.send("Je suis trop faible pour t'attribuer ce rôle.")


@bot.command(name="jeNeVeuxPlusEtre", description="Je t'enlève le role de ton choix (passé en argument).")
async def jeNeVeuxPlusEtre(ctx, *role):
    try:
        if isAdmin(ctx) or ctx.author.name == "Meatman":
            texteListe = []
            texte = ""
            for j in range(len(role)):
                texteListe.append(role[j])
            for mot in texteListe:
                texte = texte + mot + " "
            texte = texte[:len(texte) - 1]
            role_a_suprimer = discord.utils.get(ctx.guild.roles, name=f"{texte}")
            if role_a_suprimer:
                await ctx.author.remove_roles(role_a_suprimer)
                await ctx.send(f"Tu n'es plus un **{role_a_suprimer}**.")
            else:
                await ctx.send("Ce rôle n'existe pas.")
        else:
            await ctx.send("Tu es trop faible pour utiliser cette commande.")
    except discord.errors.Forbidden:
        await ctx.send("Je suis trop faible pour t'attribuer ce rôle.")


@bot.command(name="spam",
             description="Je vais spamer 10 fois le texte en argument (mention possible ;)).")
async def spam(ctx, *txt):
    if isAdmin(ctx):
        texte = []
        for mot in txt:
            texte.append(f"{mot} ")
        for msg in range(10):
            await ctx.send("".join(texte))
    else:
        await ctx.send("Vous êtes trop faible pour utiliser cette commande.")


@bot.command(name="supr", description="Je vais suprimer le nombre de messages indiqué en paramètre.")
async def supr(ctx, number: int):
    if isAdmin(ctx):
        await bot.change_presence(activity=discord.Game(name=f"suprimer {number} messages"))
        messages = await ctx.channel.history(limit=number + 1).flatten()
        for each_message in messages:
            await each_message.delete()
        await bot.change_presence()
    else:
        await ctx.send("Tu es trop faible pour utiliser cette commande.")


@bot.command(name="serverInfo",
             description="Grâce à mes grande capacités calculatoire je peut donner des stats sur ce serveur.")
async def serverInfo(ctx):
    server = ctx.guild
    numberOfTextChannels = len(server.text_channels)
    numberOfVoiceChannels = len(server.voice_channels)
    numberOfPerson = server.member_count
    message = f"Le serveur possède **{numberOfPerson} membres** et **{numberOfTextChannels} channels textuel** et **{numberOfVoiceChannels} channels vocaux**."
    await ctx.send(message)


@bot.command(name="tang",
             description="Je traduis pour toi le texte de ton message en caractère asiatique (oui c'est raciste)")
async def tang(ctx, *text):
    chinesechar = "丹书匚刀巳下呂廾工丿片乚爪冂口尸Q尺丂丁凵V山乂Y乙"
    chinesetext = []
    for word in text:
        for char in word:
            char = char.lower()
            if char.isalpha():
                index = ord(char) - ord("a")
                transformed = chinesechar[index]
                chinesetext.append(transformed)
            else:
                chinesetext.append(char)
        chinesetext.append(" ")
    await supr(ctx, 0)
    await ctx.send(str(ctx.author.mention) + " " + "".join(chinesetext))


def isAdmin(ctx):
    admin = False
    for role in ctx.author.roles:
        if role.name == "admin":
            admin = True
    return admin


bot.run(os.getenv("TOKEN"))
