from moviepy.editor import *
import os

directory = "E:\\Desktop\\TiktokCutter"

i = 1

for filename in os.listdir(directory):
    if filename.endswith(".mp4"):
        clip = VideoFileClip(filename)
        fixed_clip = clip.subclip(0, -3)

        txt_clip = TextClip("BLAZELL", fontsize=40, color='white', font="Bahnschrift")
        txt_clip = txt_clip.set_pos(('left', 'bottom')).set_duration(fixed_clip.duration)

        video = CompositeVideoClip([fixed_clip, txt_clip])

        video_name = str(i) + ".mp4"
        video.write_videofile(video_name)
        i += 1
