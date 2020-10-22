from PIL import Image

im=Image.open("./cat.jpg")

gray_im=im.convert('L')

gray_im.show()

gray_im.save("./gray_cat.jpg")