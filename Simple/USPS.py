import CSV
import SamPlot

history = CSV.get_xys_from('history.csv', include_ys=False)
SamPlot.sam_plot([1E-5*i for i in range(len(history))],
                 [x[0] for x,y in history], 'test error')
SamPlot.save_plot('virtual time', 'RMS error',
                  'SoftMax Learning Curve on USPS Data', 'Plots\\plot 4.png')

print('Tada!')
