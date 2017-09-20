from django.shortcuts import render
from comunity.forms import *

# Create your views here.
def write(request):
	if request.method == 'POST':
		form = Form(request.POST)
		if form.is_valid():
			form.save()

	else:
		form = Form()

	return render(request,'write.html', {'form':form})


def list(request):
	articleList =  Article.objects.all()
	return render(request,'list.html', {'articleList':articleList})

def view(request, num = "1"):
	article = Article.objects.get(id = num)
	return render(request,'view.html', {'article':article})
