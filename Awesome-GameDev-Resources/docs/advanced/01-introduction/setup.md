# Advanced Programming

## Table of Contents

- [Syllabus](../README.md)
- [Safe and welcoming space](#safe-and-welcoming-space)
- [Privacy and FERPA Compliance](#privacy-and-ferpa-compliance)
- [Activities](#activities)
    - [Setup Github repository](#setup-github-repository)
    - [Setup your IDE](#setup-your-ide)
    - [Setup your Assignments project](#setup-your-assignments-project)
    - [Check Github Actions](#check-github-actions)
- [Homework](#homework)

## Safe and welcoming space

TLDR: Be nice to each other, and don't copy code from the internet.

- [Code of Conduct](../../../CODE_OF_CONDUCT.md)
- [Notes on Submissions and Plagiarism](../../blog/posts/NotesOnSubmissions/NotesOnSubmissions.md)

Some assignments can be hard, and you may feel tempted to copy code from the internet. **Don't do it**. You will only hurt yourself. You will learn nothing, and you will be caught. Once you get caught, you will be reported to the Dean of Students for academic dishonesty.

If you are struggling with an assignment, please contact me in my office-hours, or via discord. I am really slow at answering emails, so do it so only if something needs to be official. Quick questions are better asked in discord by me or your peers.

## Privacy and FERPA Compliance

!!! danger inline end "FERPA WAIVER"

    If you are willing to share your final project publicly, you MUST SIGN [this FERPA waiver](../../../blog/FerpaWaiver/FerpaWaiver.md).

<iframe src="https://giphy.com/embed/e7yNPQmGUozyU" width="480" height="336" frameBorder="0" class="giphy-embed" allowFullScreen></iframe><p><a href="https://giphy.com/gifs/facebook-posts-privacy-e7yNPQmGUozyU">via GIPHY</a></p>

This class will use github extensively, in order to keep you safe, we will use private repositories. This means that only you and me will be able to see your code. In your final project, you must share it with your pair partner, and with me.

## Activities

TLDR: there is no TLDR, read the whole thing.

<iframe src="https://giphy.com/embed/H1dxi6xdh4NGQCZSvz" width="480" height="480" frameBorder="0" class="giphy-embed" allowFullScreen></iframe><p><a href="https://giphy.com/gifs/justviralnet-cat-hilarious-typing-H1dxi6xdh4NGQCZSvz">via GIPHY</a></p>

### Setup Github repository

!!! note inline end "Gitkraken"

    Optionally you might want to use GitKraken as your git user interface. Once you open it for the first time, signup using your github account with student pack associated.[:fontawesome-brands-gitkraken: Install Gitkraken](https://www.gitkraken.com/){ .md-button .md-button--primary }

1. Signup on github and apply for Github Student Pack. [:fontawesome-brands-github: Apply for Student Pack](https://education.github.com/pack){ .md-button .md-button--primary }
2. Send me your github username in class, so I will share the assignment repository with you;
3. Create a private repository by clicking "use as template" the repository [:material-source-repository: InfiniBrains/csi240](https://github.com/InfiniBrains/csi240) or [Create CSI240 repository](https://github.com/new?owner=InfiniBrains&template_name=csi240&template_owner=InfiniBrains&visibility=private){ .md-button .md-button--primary }
4. Share your repository with me. Click on settings, then collaborators, and add me as a collaborator. My username: [@tolstenko](https://github.com/tolstenko)
5. Clone your repository to your computer. You can use the command line, or any Git GUI tool. I recommend [:simple-gitkraken: GitKraken](https://www.gitkraken.com/){ .md-button .md-button--primary }

### Setup your IDE

!!! note inline end "Other IDEs"

    Optionally you might want to use any other IDE, such as Visual Studio, VSCode, XCode, NeoVim or any other, but I will not be able to help you with that.

I will use CLion in class, and I recommend you to use it as well so you can follow the same steps as me. It is free for students. And it works on Windows, Mac and Linux.

1. Apply for student license for [:simple-jetbrains: JetBrains](https://www.jetbrains.com/student/) or [:material-form-select: Apply Form](https://www.jetbrains.com/shop/eform/students){ .md-button .md-button--primary }
2. You can install [:simple-clion: CLion](https://www.jetbrains.com/clion/) only or install CLion via their [:material-toolbox: Install Toolbox](https://www.jetbrains.com/toolbox-app/){ .md-button .md-button--primary }
3. Open CLion for the first time, and login with your JetBrains account you created earlier;

### Setup your Assignments project

!!! warning inline end "Common problems"

    Your machine might not have git on your path. If so, install it from [git-scm.com](https://git-scm.com/) and make sure you tick the option to add git to your PATH.

1. Open your IDE, and click on "Open Project";
2. Select the folder where you cloned your repository;
3. Click on "Open as Project" or "Open as CMake Project";
4. Wait for CMake to finish generating the project;
5. On the top right corner, select the target you want to run/debug;

### Check Github Actions

!!! note inline end "Github Actions"

    Github Actions is a CI/CD tool that will run your tests automatically when you push your code to github. It will also run your tests when you create a pull request. It is a great tool to make sure your code is always working.
    
    You might want to explore the folder `.github/workflows` to see how it works, but you don't need to change anything there.

![tests-meme.png](../../tests-meme.png)

Every commit you push to your repository will be automatically tested through Github Actions. You can see the results of the tests by clicking on the "Actions" tab on your repository.

1. Go to your repository on github;
2. Click on the "Actions" tab;
3. Click on the "Build and Test" action;
4. Click on the latest commit;
5. On the jobs panel, Click on the assignment you want to see the results;
6. Read the logs to see if your tests passed or failed;
7. It is your job to read the README.md from every assignment and fulfill the requirements;
8. You can run/debug the tests locally by targeting the assignmentXX_tests;

## Homework

<iframe src="https://giphy.com/embed/cFkiFMDg3iFoI" width="480" height="269" frameBorder="0" class="giphy-embed" allowFullScreen></iframe><p><a href="https://giphy.com/gifs/git-merge-cFkiFMDg3iFoI">via GIPHY</a></p>

1. Read the [Syllabus](../README.md) fully. Pay attention to the schedule, outcomes and grading;
2. Do all assignments on Canvas, specially the git training;