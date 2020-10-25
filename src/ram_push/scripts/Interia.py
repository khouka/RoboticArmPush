print"This is a basic interia calculator for the cylinder and box links"

print"For box shaped links"
m = input('mass: ')
x = input('input the length(x): ')
y = input('input the width(y): ')
z = input('input the height(z): ')

ixx = 0.0833333 * m * (y**2 + z**2)
iyy = 0.0833333 * m * (x**2 + z**2)
izz = 0.0833333 * m * (x**2 + y**2)

#################################
#print"For cylinder shaped links"
#m = input('mass: ')
#r = input('input the radius')
#l = input('input the length')

#ixx = 0.0833333 * m * (3*r**2+l**2)
#iyy = 0.0833333 * m * (3*r*r+l*l)
#izz = 0.5 * m * r**2 
#################################

# Output
print"mass = ", m
print"ixx = ", ixx
print"iyy = ", iyy
print"izz = ", izz








