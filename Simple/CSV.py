'''.............................
   Creation 2015 by Samuel Tenka
   .............................'''
''' reader/writer of CSV files of form:
---HEADING LINE
---DATA LINES of form
------ID,x1,x2,x3,...,xn,y'''

def get_row(file):
   return file.readline().split(',')[1:] ## neglect first val (ID#).
def get_xys_from(filename, include_ys=True):
   ''' return format [((x1,...,xn), y),
                      ((x1,...,xn), y),...]'''
   xys = []
   with open(filename) as f:
      f.readline() ## headings, to be discarded
      for row in iter(lambda:get_row(f), []):
         values = [eval(s) for s in row]
         xy = (values[:-1], values[-1]) if include_ys else \
              (values, None)
         xys.append(xy)
   return xys

csv_headings = 'id,rolling_speed,elevation_speed,elevation_jerk,elevation,roll,elevation_acceleration,controller_input\n'
csv_headings_no_xs = 'id,controller_input\n'
def put_row(file, row_id, row):
   strings = [str(row_id)] + [str(v) for v in row]
   file.write(','.join(strings) + '\n')
def put_xys_to(filename, xys, initial_row_id=1, include_xs=True):
   with open(filename, 'w') as f:
      f.write(csv_headings if include_xs else csv_headings_no_xs)
      for (x,y) in xys:
         row = x+[y] if include_xs else [y]
         put_row(f, initial_row_id, row)
         initial_row_id += 1
